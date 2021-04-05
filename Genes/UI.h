//
// Created by georg on 4/5/2021.
//
#pragma once
#include "Service.h"

class ui {
private:
    Service& service;
    static void print_menu();
public:
    explicit ui(Service& service1): service{service1}{}

    void addUI();

    void showUI();

    void showFilteredUI();

    void longestCommUI();

    void start_application();


};


