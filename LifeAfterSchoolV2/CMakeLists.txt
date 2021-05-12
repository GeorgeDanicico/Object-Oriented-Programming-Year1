cmake_minimum_required(VERSION 3.17)
project(a89_GeorgeDanicico)

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

add_executable(a89_GeorgeDanicico LifeAfterSchool/main.cpp
        LifeAfterSchool/GUI.cpp
        LifeAfterSchool/GUI.h
        LifeAfterSchool/main.cpp
        LifeAfterSchool/tests.h
        LifeAfterSchool/tests.cpp
        LifeAfterSchool/LifeAfterSchool.cpp
        LifeAfterSchool/LifeAfterSchool.h
        LifeAfterSchool/LifeAfterSchool.qrc
        LifeAfterSchool/LifeAfterSchool.ui
        LifeAfterSchool/Exception.h
        LifeAfterSchool/domain/date.cpp
        LifeAfterSchool/domain/date.h
        LifeAfterSchool/domain/domain.cpp
        LifeAfterSchool/domain/domain.h
        LifeAfterSchool/Service/service.h
        LifeAfterSchool/Service/service.cpp
        LifeAfterSchool/Repository/database_repo.h
        LifeAfterSchool/Repository/file_repo.h
        LifeAfterSchool/Repository/repo.h
        LifeAfterSchool/Store/store.h
        LifeAfterSchool/Store/store_csv.h
        LifeAfterSchool/Store/store_html.h
        LifeAfterSchool/Store/store_csv.cpp
        LifeAfterSchool/Store/store_html.cpp
        LifeAfterSchool/configuration.txt
        sqlite/sqlite3.h
        sqlite/sqlite3.c
        sqlite/sqlite3ext.h
        )
target_link_libraries(a89_GeorgeDanicico Qt5::Widgets Qt5::Charts)