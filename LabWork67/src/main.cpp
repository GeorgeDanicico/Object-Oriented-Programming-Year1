// src.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Repository/repo.h"
#include "Service/service.h"
#include "Interface/ui.h"
#include "Store/store_html.h"
#include "Store/store_csv.h"
#include "tests.h"
#include "Repository/database_repo.h"

int main()
{
    all_tests();

    string file_repo;
    cout << "\nEnter the repo type(file/db): ";
    getline(cin, file_repo);
    string file, user_file;
    vector<TElem> dv1, dv2;
    IRepo<TElem>* admin_repo;
    IRepo<TElem>* user_repo;

    if(file_repo == "db") {
        // setting the environment for the database repo.
        file = "../events_database.db";
        user_file = "../user_database.db";
        admin_repo = new Data_Repo<TElem>{dv1, file};
        user_repo = new Data_Repo<TElem>{dv2, user_file};
    }
    else if(file_repo == "file"){
        // setting the environment for the text file repo.
        file = "../Events_list.txt";
        user_file = "../User_list.txt";
        admin_repo = new Repo<TElem>{dv1, file};
        user_repo = new Repo<TElem>{dv2, user_file};
    }
    else{
        cout << "Invalid repo... Exiting...\n";
        exit(0);
    }

    string file_type;
    cout << "\nEnter the type of the file: ";
    getline(cin, file_type);

    if(file_type == "csv"){
        Store_csv csv{dv2, "../example.csv"};
        Service service{admin_repo, user_repo, csv};
        UI ui{service};
        ui.start_application();
    }
    else if(file_type == "html"){
        Store_html html{dv2, "../example.html"};
        Service service{admin_repo, user_repo, html};
        UI ui{service};
        ui.start_application();
    }
    else{
        cout<<"Invalid type ... Exiting...\n";
    }

    delete user_repo;
    delete admin_repo;

    return 0;
}
