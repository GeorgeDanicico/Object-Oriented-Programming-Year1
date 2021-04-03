#pragma once
#include "service.h"

class UI{
private:
    Service& service;

    static void entry_menu();

    static void print_menu_admin();
    void admin_UI();

    static void print_menu_user();
    void user_UI();

    static std::string readLine(std::string type);


    void addUI();
    void deleteUI(std::string mode);
    void updateUI();
    void seeUI(std::string mode);

    void createUI();
    void listUI();
public:
    UI(Service& service): service{service}{}

    ~UI();

    void start_application();

};