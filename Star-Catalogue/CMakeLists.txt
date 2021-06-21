cmake_minimum_required(VERSION 3.17)
project(Star_Catalogue)

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

add_executable(Star_Catalogue main.cpp
        domain.h
        Repository.h
        Repository.cpp
        service.h
        Observer.h
        Window.h
        Window.cpp
        Table.h
        Table.cpp
        ViewWindow.cpp
        ViewWindow.h)
target_link_libraries(Star_Catalogue Qt5::Widgets Qt5::Charts)