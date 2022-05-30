include($$PWD/../../Input.pri)

DESTDIR = $$PLUGINS_PREFIX/Input

HEADERS += decoderuadefactory.h \
           decoder_uade.h \
           uadehelper.h \
           uademetadatamodel.h
           
SOURCES += decoderuadefactory.cpp \
           decoder_uade.cpp \
           uadehelper.cpp\
           uademetadatamodel.cpp

INCLUDEPATH += $$EXTRA_PREFIX/libttk/include

unix{
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
    LIBS += -L$$EXTRA_PREFIX/libttk/lib -luade$$STATIC_LIBRARY_SUFFIX
}

win32{
    LIBS += -L$$EXTRA_PREFIX/libttk/lib -luade -lws2_32
}