QT += widgets core gui

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        addingcard.cpp \
        card.cpp \
        cardfire.cpp \
        container.cpp \
        customdateinput.cpp \
        editcard.cpp \
        employee.cpp \
        employeelistwidget.cpp \
        employeemanager.cpp \
        main.cpp \
        table_widget.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    addingcard.h \
    card.h \
    cardfire.h \
    container.h \
    customdateinput.h \
    editcard.h \
    employee.h \
    employeelistwidget.h \
    employeemanager.h \
    special.h \
    table_widget.h

RESOURCES += \
 res.qrc
