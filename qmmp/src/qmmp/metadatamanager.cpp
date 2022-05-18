#include <QFile>
#include <QFileInfo>
#include <QBuffer>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QImageReader>
#include "decoder.h"
#include "decoderfactory.h"
#include "abstractengine.h"
#include "inputsource.h"
#include "qmmpsettings.h"
#include "metadatamanager.h"

#define COVER_CACHE_SIZE 10

MetaDataManager* MetaDataManager::m_instance = nullptr;

MetaDataManager::MetaDataManager()
    : m_settings(QmmpSettings::instance()),
      m_mutex(QMutex::Recursive)
{

}

MetaDataManager::~MetaDataManager()
{
    clearCoverCache();
}

QList<TrackInfo*> MetaDataManager::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *ignoredPaths) const
{
    QList<TrackInfo*> playlist;
    DecoderFactory *fact = nullptr;
    EngineFactory *efact = nullptr;
    QStringList dummyList;
    if(!ignoredPaths)
        ignoredPaths = &dummyList;

    if(!path.contains("://")) //local file
    {
        if(!QFile::exists(path))
            return playlist;

        if(!(fact = Decoder::findByFilePath(path, m_settings->determineFileTypeByContent())))
            efact = AbstractEngine::findByFilePath(path);
    }
    else
    {
        QString scheme = path.section("://",0,0);
        if(InputSource::findByUrl(path))
        {
            playlist << new TrackInfo(path);
        }
        else
        {
            for(DecoderFactory *f : Decoder::factories())
            {
                if(f->properties().protocols.contains(scheme) && Decoder::isEnabled(f))
                {
                    fact = f;
                    break;
                }
            }
        }
    }

    if(fact)
        playlist = fact->createPlayList(path, parts, ignoredPaths);
    else if(efact)
        playlist = efact->createPlayList(path, parts, ignoredPaths);

    for(TrackInfo *info : qAsConst(playlist))
    {
        if(info->value(Qmmp::DECODER).isEmpty() && (fact || efact))
            info->setValue(Qmmp::DECODER, fact ? fact->properties().shortName : efact->properties().shortName);
        if(info->value(Qmmp::FILE_SIZE).isEmpty() && !path.contains("://"))
            info->setValue(Qmmp::FILE_SIZE, QFileInfo(path).size());
    }
    return playlist;
}

MetaDataModel* MetaDataManager::createMetaDataModel(const QString &path, bool readOnly) const
{
    DecoderFactory *fact = nullptr;
    EngineFactory *efact = nullptr;

    if(!path.contains("://")) //local file
    {
        if(!QFile::exists(path))
            return nullptr;
        else if((fact = Decoder::findByFilePath(path, m_settings->determineFileTypeByContent())))
            return fact->createMetaDataModel(path, readOnly);
        else if((efact = AbstractEngine::findByFilePath(path)))
            return efact->createMetaDataModel(path, readOnly);
        return nullptr;
    }
    else
    {
        QString scheme = path.section("://",0,0);
        MetaDataModel *model = nullptr;
        if((fact = Decoder::findByProtocol(scheme)))
        {
            return fact->createMetaDataModel(path, readOnly);
        }
        for(EngineFactory *efact : AbstractEngine::enabledFactories())
        {
            if(efact->properties().protocols.contains(scheme))
                model = efact->createMetaDataModel(path, readOnly);
            if(model)
                return model;
        }
    }
    return nullptr;
}

QStringList MetaDataManager::filters() const
{
    QStringList filters;
    for(const DecoderFactory *fact : Decoder::enabledFactories())
    {
        if(!fact->properties().filters.isEmpty())
            filters << fact->properties().description + " (" + fact->properties().filters.join(" ") + ")";
    }
    for(const EngineFactory *fact : AbstractEngine::enabledFactories())
    {
        if(!fact->properties().filters.isEmpty())
            filters << fact->properties().description + " (" + fact->properties().filters.join(" ") + ")";
    }
    return filters;
}

QStringList MetaDataManager::nameFilters() const
{
    QStringList filters;
    filters << Decoder::nameFilters();
    filters << AbstractEngine::nameFilters();
    if(m_settings->determineFileTypeByContent())
        filters << "*";
    filters.removeDuplicates();
    return filters;
}

QStringList MetaDataManager::protocols() const
{
    QStringList p;
    p << InputSource::protocols();
    p << Decoder::protocols();
    p << AbstractEngine::protocols();
    p.removeDuplicates();
    return p;
}

QList<RegularWrapper> MetaDataManager::regExps() const
{
    return InputSource::regExps();
}

bool MetaDataManager::supports(const QString &fileName) const
{
    if(!fileName.contains("://")) //local file
    {
        if(!QFile::exists(fileName))
            return false;
        if(Decoder::findByFilePath(fileName))
            return true;
        else if(AbstractEngine::findByFilePath(fileName))
            return true;
        return false;
    }
    return false;
}

QPixmap MetaDataManager::getCover(const QString &url) const
{
    QMutexLocker locker(&m_mutex);
    for(int i = 0; i < m_cover_cache.count(); ++i)
    {
        if(m_cover_cache[i]->url == url)
            return m_cover_cache[i]->coverPixmap;
    }

    m_cover_cache << createCoverCacheItem(url);

    while(m_cover_cache.count() > COVER_CACHE_SIZE)
        delete m_cover_cache.takeFirst();

    return m_cover_cache.back()->coverPixmap;
}

QString MetaDataManager::getCoverPath(const QString &url) const
{
    QMutexLocker locker(&m_mutex);
    for(int i = 0; i < m_cover_cache.count(); ++i)
    {
        if(m_cover_cache[i]->url == url)
            return m_cover_cache[i]->coverPath;
    }

    m_cover_cache << createCoverCacheItem(url);

    while(m_cover_cache.count() > COVER_CACHE_SIZE)
        delete m_cover_cache.takeFirst();

    return m_cover_cache.back()->coverPath;
}

QString MetaDataManager::findCoverFile(const QString &fileName) const
{
    if(!m_settings->useCoverFiles())
        return QString();

    if(!QFile::exists(fileName))
    {
        return QString();
    }

    const QFileInfoList &l = findCoverFiles(QFileInfo(fileName).absoluteDir(), m_settings->coverSearchDepth());
    return l.isEmpty() ? QString() : l.at(0).filePath();
}

QFileInfoList MetaDataManager::findCoverFiles(QDir dir, int depth) const
{
    dir.setFilter(QDir::Files | QDir::Hidden);
    dir.setSorting(QDir::Name);
    QFileInfoList file_list = dir.entryInfoList(m_settings->coverNameFilters());

    const auto fileListCopy = file_list; //avoid container modification
    for(const QFileInfo &fin : qAsConst(fileListCopy))
    {
        if(QDir::match(m_settings->coverNameFilters(false), fin.fileName()))
            file_list.removeAll(fin);

        if(QImageReader::imageFormat(fin.filePath()).isEmpty()) //remove unsupported image formats
            file_list.removeAll(fin.fileName());
    }
    if(!depth || !file_list.isEmpty())
        return file_list;
    depth--;
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    const QFileInfoList dir_info_list = dir.entryInfoList();
    for(const QFileInfo &fin : qAsConst(dir_info_list))
    {
        file_list << findCoverFiles(QDir(fin.absoluteFilePath()), depth);
    }
    return file_list;
}

MetaDataManager::CoverCacheItem *MetaDataManager::createCoverCacheItem(const QString &url) const
{
    CoverCacheItem *item = new CoverCacheItem;
    item->url = url;
    if(!url.contains("://") && m_settings->useCoverFiles())
        item->coverPath = findCoverFile(url);

    if(item->coverPath.isEmpty())
    {
        MetaDataModel *model = createMetaDataModel(url, true);
        if(model)
        {
            item->coverPath = model->coverPath();
            item->coverPixmap = model->cover();
            delete model;
        }
    }

    if(!item->coverPath.isEmpty() && item->coverPixmap.isNull())
        item->coverPixmap = QPixmap(item->coverPath);

    if(item->coverPixmap.width() > 1024 || item->coverPixmap.height() > 1024)
        item->coverPixmap = item->coverPixmap.scaled(1024, 1024, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    return item;
}

void MetaDataManager::clearCoverCache()
{
    qDeleteAll(m_cover_cache);
    m_cover_cache.clear();
}

void MetaDataManager::prepareForAnotherThread()
{
    //this hack should load all required plugins
    InputSource::enabledFactories();
    Decoder::enabledFactories();
    AbstractEngine::enabledFactories();
}

MetaDataManager *MetaDataManager::instance()
{
    if(!m_instance)
    {
        m_instance = new MetaDataManager();
        qAddPostRoutine(&MetaDataManager::destroy);
    }
    return m_instance;
}

void MetaDataManager::destroy()
{
    if(m_instance)
        delete m_instance;
    m_instance = nullptr;
}
