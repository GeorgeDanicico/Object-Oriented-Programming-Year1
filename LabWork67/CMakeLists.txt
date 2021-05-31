cmake_minimum_required(VERSION 3.17)
project(a67_GeorgeDanicico)

set(CMAKE_CXX_STANDARD 14)

add_executable(a67_GeorgeDanicico
        src/Exception.h
        src/main.cpp
        src/domain/domain.h
        src/domain/domain.cpp
        src/domain/date.cpp
        src/domain/date.h
        src/Repository/database_repo.h
        src/Repository/repo.h
        src/Repository/file_repo.h
        src/Service/service.h
        src/Service/service.cpp
        src/Store/store.h
        src/Store/store_csv.cpp
        src/Store/store_csv.h
        src/Store/store_html.cpp
        src/Store/store_html.h
        src/tests.cpp
        src/tests.h
        src/Interface/ui.h
        src/Interface/ui.cpp
        sqlite/sqlite3.h
        sqlite/sqlite3.c
        sqlite/sqlite3ext.h)