cmake_minimum_required(VERSION 3.17)
project(Observer_ChatApp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH C:\\Qt\\5.15.2\\mingw81_64)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
find_package(Qt5Widgets)
find_package(Qt5Charts)

add_executable(Observer_ChatApp main.cpp
        ChatWindow.cpp
        ChatSesssion.h
        ChatWindow.h
        Observers.h
        UserMessage.h)
target_link_libraries(Observer_ChatApp Qt5::Widgets Qt5::Charts)