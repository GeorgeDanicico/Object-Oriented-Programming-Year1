//
// Created by georg on 4/15/2021.
//

#include "store_csv.h"

void Store_csv::write() {
    ofstream fout;
    if(!this->filename.empty()) {
        fout.open(filename);

        if(!fout)
            throw ImplementedException("The file couldn't be opened.\n");

        for (auto &elem : this->_storage->get_all()) {
            fout << elem.getTitle() << ",";
            fout << elem.getDescription() << ",";
            fout << elem.getLink() << ",";
            fout << elem.getDate() << ",";
            fout << elem.getPeopleNr() << "\n";
        }
    }
}

void Store_csv::open() {
    if(!this->filename.empty()) {
        string command = "start " + this->filename;
        system(command.c_str());
    }
}
