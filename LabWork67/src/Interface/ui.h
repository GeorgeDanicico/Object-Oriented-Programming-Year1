#pragma once
#include "../Service/service.h"

class UI{
private:
    Service& service;

    static void entry_menu();

    static void print_menu_admin();
    void admin_UI();

    static void print_menu_user();
    void user_UI();

    static string readLine(const string& type);


    void addUI(const string& mode);
    void deleteUI(const string& mode);
    void updateUI(const string& mode);
    void seeUI(const string& mode);

    void createUI(const string& mode);
    void listUI(const string& mode);
    void showfile(const string& mode);
public:
    explicit UI(Service& service): service{service}{}

    ~UI();

    void start_application();

};

typedef void (UI::*function)();
typedef void (UI::*paramfunction)(const string& mode);