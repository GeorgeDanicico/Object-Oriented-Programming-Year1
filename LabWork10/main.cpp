
#include <QtWidgets/QApplication>
#include <fstream>
#include <iostream>
#include "repo.h"
#include "service.h"
#include "store_html.h"
#include "store_csv.h"
#include "tests.h"
#include "database_repo.h"
#include <memory>
#include "GUI.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    string file_repo;
    string admin_file, user_file;
    vector<TElem> dv1, dv2;
    vector<Operation*> au, ar, uu, ur;
    unique_ptr<IRepo<TElem>> admin_repo;
    unique_ptr<IRepo<TElem>> user_repo;
    unique_ptr<Abstract_store> Store;

    ifstream settings;
    settings.open("configuration.txt", ios::in);
    string repository, storage;
    getline(settings, repository);
    getline(settings, storage);

    if (repository == "file") {
        admin_file = "Events_list.txt";
        user_file = "User_list.txt";
        admin_repo = make_unique<Repo<TElem>>(dv1, admin_file);
        user_repo = make_unique<Repo<TElem>>(dv2, user_file);
    }
    else {
        admin_file = "events_database.db";
        user_file = "user_database.db";
        admin_repo = make_unique<Repo<TElem>>(dv1, admin_file);
        user_repo = make_unique<Repo<TElem>>(dv2, user_file);

    }
    if (storage == "csv") {
        Store = make_unique<Store_csv>(user_repo.get(), "example.csv" );
        Service service{ admin_repo.get(), user_repo.get(), Store.get(),au, ar, uu, ur };
        GUI gui{ service };
        gui.show();
        return a.exec();
    }
    else {
        Store = make_unique<Store_html>(user_repo.get(), "example.html" );
        Service service{ admin_repo.get(), user_repo.get(), Store.get(), au, ar, uu, ur };
        GUI gui{ service };
        gui.show();
        return a.exec();
    }
}
