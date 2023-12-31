#include "musicabstractsongslisttablewidget.h"
#include "musicurlutils.h"
#include "musictoastlabel.h"
#include "musicfileinformationwidget.h"
#include "musicrightareawidget.h"
#include "musicsongsharingwidget.h"
#include "musicdownloadwidget.h"
#include "musicapplication.h"
#include "musicleftareawidget.h"

MusicAbstractSongsListTableWidget::MusicAbstractSongsListTableWidget(QWidget *parent)
    : MusicAbstractSongsListTableWidget(-1, parent)
{

}

MusicAbstractSongsListTableWidget::MusicAbstractSongsListTableWidget(int index, QWidget *parent)
    : MusicSmoothMovingTableWidget(parent),
      m_toolIndex(index),
      m_playRowIndex(-1),
      m_songs(nullptr),
      m_hasParentToolIndex(true)
{

}

MusicAbstractSongsListTableWidget::~MusicAbstractSongsListTableWidget()
{

}

void MusicAbstractSongsListTableWidget::setSongsList(MusicSongList *songs)
{
    m_songs = songs;
    updateSongsList(*songs);
}

void MusicAbstractSongsListTableWidget::updateSongsList(const MusicSongList &songs)
{
    Q_UNUSED(songs);
}

void MusicAbstractSongsListTableWidget::selectRow(int index)
{
    MusicSmoothMovingTableWidget::selectRow(index);
}

int MusicAbstractSongsListTableWidget::totalHeight() const
{
    int height = 0;
    for(int i = 0; i < rowCount(); ++i)
    {
        height += rowHeight(i);
    }
    return height;
}

void MusicAbstractSongsListTableWidget::setToolIndex(int index)
{
    m_toolIndex = index;
}

void MusicAbstractSongsListTableWidget::removeItemAt()
{

}

void MusicAbstractSongsListTableWidget::playClicked()
{
    if(!isValid())
    {
        return;
    }

    Q_EMIT cellDoubleClicked(currentRow(), 0);
}

void MusicAbstractSongsListTableWidget::removeItemAll()
{
    selectAll();
    removeItemAt();

    bool state = false;
    Q_EMIT isCurrentIndex(state);

    if(rowCount() == 0 && state)
    {
        MusicApplication::instance()->playIndexBy(TTK_NORMAL_LEVEL);
    }
}

void MusicAbstractSongsListTableWidget::openFileDir()
{
    if(!isValid())
    {
        return;
    }

    const QString &path = !m_songs->isEmpty() ? m_songs->at(currentRow()).path() : QString();
    if(QFileInfo(path).baseName() == TTK::Algorithm::mdII(currentSongName(), ALG_ARC_KEY, true))
    {
        //cache song should not allow open url
        return;
    }

    if(!TTK::Url::openUrl(QFileInfo(path).absoluteFilePath()))
    {
        MusicToastLabel::popup(tr("The file has been moved or does not exist"));
    }
}

void MusicAbstractSongsListTableWidget::showFileInformation()
{
    if(!isValid())
    {
        return;
    }

    MusicFileInformationWidget widget;
    widget.setFileInformation(currentSongPath());
    widget.exec();
}

void MusicAbstractSongsListTableWidget::showMovieQueryWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicRightAreaWidget::instance()->showVideoSearchedFound(currentSongName(), QString());
}

void MusicAbstractSongsListTableWidget::showAlbumQueryWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicRightAreaWidget::instance()->showAlbumFound(currentSongName(), QString());
}

void MusicAbstractSongsListTableWidget::showSimilarQueryWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicRightAreaWidget::instance()->showSimilarFound(currentSongName());
}

void MusicAbstractSongsListTableWidget::showSongSharedWidget()
{
    if(!isValid())
    {
        return;
    }

    QVariantMap data;
    data["songName"] = currentSongName();

    MusicSongSharingWidget widget;
    widget.setData(MusicSongSharingWidget::Module::Song, data);
    widget.exec();
}

void MusicAbstractSongsListTableWidget::showDownloadWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicDownloadWidget *download = new MusicDownloadWidget;
    download->setSongName(currentSongName(), MusicAbstractQueryRequest::QueryType::Music);
    download->show();
}

void MusicAbstractSongsListTableWidget::showPlayedMovieQueryWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicRightAreaWidget::instance()->showVideoSearchedFound(songName(m_playRowIndex), QString());
}

void MusicAbstractSongsListTableWidget::showPlayedSimilarQueryWidget()
{
    if(!isValid())
    {
        return;
    }

    MusicRightAreaWidget::instance()->showSimilarFound(songName(m_playRowIndex));
}

void MusicAbstractSongsListTableWidget::showPlayedSongSharedWidget()
{
    if(!isValid())
    {
        return;
    }

    QVariantMap data;
    data["songName"] = songName(m_playRowIndex);

    MusicSongSharingWidget widget;
    widget.setData(MusicSongSharingWidget::Module::Song, data);
    widget.exec();
}

void MusicAbstractSongsListTableWidget::createMoreMenu(QMenu *menu)
{
    menu->setStyleSheet(TTK::UI::MenuStyle02);
    menu->addAction(QIcon(":/contextMenu/btn_similar"), tr("Similar"), this, SLOT(showSimilarQueryWidget()));
    menu->addAction(QIcon(":/contextMenu/btn_share"), tr("Share"), this, SLOT(showSongSharedWidget()));
}

QString MusicAbstractSongsListTableWidget::currentSongPath() const
{
    return isValid() ? songPath(currentRow()) : QString();
}

QString MusicAbstractSongsListTableWidget::songPath(int index) const
{
    return !m_songs->isEmpty() ? m_songs->at(index).path().trimmed() : QString();
}

QString MusicAbstractSongsListTableWidget::currentSongName() const
{
    return isValid() ? songName(currentRow()) : QString();
}

QString MusicAbstractSongsListTableWidget::songName(int index) const
{
    if(rowCount() == 0 || index < 0)
    {
        return QString();
    }

    return !m_songs->isEmpty() ? m_songs->at(index).name().trimmed() : QString();
}
