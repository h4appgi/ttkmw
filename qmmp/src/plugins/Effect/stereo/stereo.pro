include($$PWD/../../plugins.pri)

DESTDIR = $$PLUGINS_PREFIX/Effect

HEADERS += stereoplugin.h \
           effectstereofactory.h \
           settingsdialog.h

SOURCES += stereoplugin.cpp \
           effectstereofactory.cpp \
           settingsdialog.cpp

FORMS += settingsdialog.ui

unix{
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
}
