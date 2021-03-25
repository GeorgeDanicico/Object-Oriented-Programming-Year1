cmake_minimum_required(VERSION 3.17)
project(a45_GeorgeDanicico)

set(CMAKE_CXX_STANDARD 14)

add_executable(a45_GeorgeDanicico src/main.cpp
        src/domain.h
        src/domain.cpp
        src/date.cpp
        src/date.h
        src/dynamicArray.cpp
        src/dynamicArray.h
        src/tests.h
        src/tests.cpp
        src/repo.cpp
        src/repo.h
        src/service.cpp
        src/service.h
        src/ui.cpp
        src/ui.h)