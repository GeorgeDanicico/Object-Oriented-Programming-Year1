cmake_minimum_required(VERSION 3.17)
project(PracticalExamProject)

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

add_executable(PracticalExamProject main.cpp
        domain.h
        Repo.h
        Repo.cpp
        Service.h
        Service.cpp
        ProgWindow.cpp
        ProgWindow.h
        Table.cpp
        Table.h
        Observer.h
        Statistics.cpp
        Statistics.h)
target_link_libraries(PracticalExamProject Qt5::Widgets Qt5::Charts)