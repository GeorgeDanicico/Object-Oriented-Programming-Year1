//
// Created by georg on 4/15/2021.
//

#include "store_html.h"

void Store_html::write() {
    if(!this->filename.empty()){
        fstream fout;
        fout.open(this->filename, ios::out);
        if(!fout)
            throw ImplementedException("The file couldn't be opened.\n");

        fout<<"<!DOCTYPE html>\n<html>\n<head>\n<title>My Events</title>\n</head>";
        fout <<"<body>\n<table border="<<1<<">\n";
        fout<<"<tr>\n";
        fout <<"<td>Title</td>\n";
        fout <<"<td>Description</td>\n";
        fout <<"<td>Link</td>\n";
        fout <<"<td>People</td>\n";
        fout <<"<td>Date</td>\n";
        fout <<"</tr>\n";

        for(auto& elem : this->_storage->get_all()){
            fout<<"<tr>\n";
            fout <<"<td>"<<elem.getTitle()<<"</td>\n";
            fout <<"<td>"<<elem.getDescription()<<"</td>\n";
            fout <<"<td><a href="<<elem.getLink()<<">"<< elem.getLink()<<"</a></td>\n";
            fout <<"<td>"<<elem.getPeopleNr()<<"</td>\n";
            fout <<"<td>"<<elem.getDate()<<"</td>\n";
            fout <<"</tr>\n";
        }
        fout <<"</table>\n</body>\n</html>\n";
        fout.close();
    }
}

void Store_html::open() {
    if(!this->filename.empty()) {
        string command = "start " + this->filename;
        system(command.c_str());
    }
}
