TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    actoritem.cpp \
    enemy.cpp \
    engine.cpp \
    keypresseater.cpp \
    main.cpp \
    gamewindow.cpp \
    player.cpp \
    city.cpp \
    resultdialog.cpp \
    startdialog.cpp \
    statistics.cpp \
    bullet.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    actoritem.hh \
    enemy.hh \
    engine.hh \
    gamewindow.hh \
    keypresseater.hh \
    player.hh \
    interfaces/iactor.hh \
    city.hh \
    resultdialog.hh \
    startdialog.hh \
    statistics.hh \
    bullet.hh

FORMS += \
    gamewindow.ui \
    resultdialog.ui \
    startdialog.ui

RESOURCES +=
