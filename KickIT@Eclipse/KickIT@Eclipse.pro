######################################################################
# Automatically generated by qmake (3.0) Mo. Mai 15 22:36:31 2017
######################################################################

TEMPLATE = app
QT += widgets
TARGET = KickIT@Eclipse
INCLUDEPATH += .
CONFIG += qt debug

# Input
HEADERS += BallTracking/BallTrackerImpl.hpp \
           BallTracking/BallTrackerInterface.hpp \
           DataType/BallPos.hpp \
           DataType/BallStatus.hpp \
           RowControl/MotorCommunicatorImpl.hpp \
           RowControl/MotorCommunicatorInterface.hpp \
           RowControl/RowControllerImpl.hpp \
           RowControl/RowControllerInterface.hpp \
           RowControl/TableControllerImpl.hpp \
           RowControl/TableControllerInterface.hpp \
           VirtualKicker/BallTrackerMock.hpp \
           VirtualKicker/TableControllerMock.hpp \
           VirtualKicker/VirtualKicker.hpp \
           VirtualKicker/VirtualKickerWindow.hpp
SOURCES += KickIT@Eclipse.cpp \
           BallTracking/BallTrackerImpl.cpp \
           RowControl/MotorCommunicatorImpl.cpp \
           RowControl/RowControllerImpl.cpp \
           RowControl/TableControllerImpl.cpp \
           VirtualKicker/BallTrackerMock.cpp \
           VirtualKicker/TableControllerMock.cpp \
           VirtualKicker/VirtualKickerWindow.cpp
