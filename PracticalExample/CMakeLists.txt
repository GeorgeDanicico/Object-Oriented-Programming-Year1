cmake_minimum_required(VERSION 3.17)
project(PracticalExample)

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

set(CMAKE_CXX_STANDARD 14)

add_executable(PracticalExample main.cpp
        Domain.h
        Repository.cpp
        Repository.h
        Service.h
        Observer.h
        Window.cpp
        Window.h
        Table.h
        Table.cpp
        test.cpp
        test.h
        )


target_link_libraries(PracticalExample Qt5::Widgets Qt5::Charts)