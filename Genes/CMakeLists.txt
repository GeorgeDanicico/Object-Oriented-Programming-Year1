cmake_minimum_required(VERSION 3.17)
project(t1_GeorgeDanicico)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_GeorgeDanicico main.cpp
        domain.h
        domain.cpp
        Repo.cpp
        Repo.h
        Service.cpp
        Service.h
        UI.cpp
        UI.h)