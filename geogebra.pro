TARGET     = geogebra
CONFIG    += staticlib
TEMPLATE   = lib
#######################################################################################
CONFIG += c++11

INCLUDEPATH += ./include
INCLUDEPATH += ../base/include

SOURCES += ./*.cpp
HEADERS += ./*.h

