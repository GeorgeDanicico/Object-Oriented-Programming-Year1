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
    std::string user_file = "../event_list.txt";
    std::string empty_file;
    DynamicVector<TElem> dv1, dv2;
    Repository admin_repo{dv1, file};
    Repository user_repo{dv2, user_file};

    Service service{admin_repo, user_repo};

    UI ui{service};
    ui.start_application();

    return 0;
}
