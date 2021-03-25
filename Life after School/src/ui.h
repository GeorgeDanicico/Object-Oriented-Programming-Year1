#pragma once
#include "service.h"

class UI{
private:
    Service& admin_service;
    Service& user_service;

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
    explicit UI(Service& admin_serv, Service& user_serv):admin_service{admin_serv}, user_service{user_serv}{}

    ~UI();

    void start_application();

};