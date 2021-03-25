// src.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "dynamicArray.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include "tests.h"

int main()
{
    all_tests();

    std::string file = "../events2.txt";
    std::string user_file;
    DynamicVector<TElem> dv1, dv2;
    Repository admin_repo{dv1, file};
    Service admin_service{admin_repo};

    Repository user_repo{dv2, user_file};
    Service user_service{user_repo};
    UI* ui = new UI(admin_service, user_service);
    ui->start_application();
    delete ui;

    return 0;
}
