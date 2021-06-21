//
// Created by georg on 6/21/2021.
//

#include "Repository.h"

Repo::Repo(string filename, string filename1, bool save):filename1{filename}, filename2{filename1}, save{save}{
    this->load_users();
    this->load_issues();
}

void Repo::save_issues() {
    ofstream fout(this->filename2);
    string line;
    for(auto& elem : this->issues){
        line.clear();
        line = line + elem.getDescription() + ";" + elem.getStatus() + ";" + elem.getReporter() + ";" + elem.getSolver() + "\n";
        fout << line;
    }
    fout.close();
}

void Repo::save_users() {
    ofstream fout(this->filename1);
    string line;
    for(auto& elem : this->users){
        line.clear();
        line = line + elem.getName() + ";" + elem.getType() + "\n";
        fout << line;
    }
    fout.close();
}

void Repo::load_users() {
    ifstream fin(this->filename1);
    string line;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, name, type;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(name.empty())
                name = token;

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        type = line;
        line.clear();
        User new_element{name, type};
        this->users.push_back(new_element);

    }
    fin.close();
}

void Repo::load_issues() {
    ifstream fin(this->filename2);
    string line;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, description, status, reporter, solver;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(description.empty())
                description = token;
            else if(status.empty())
                status = token;
            else if(reporter.empty()){
                reporter = token;
            }

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        solver = line;
        line.clear();
        Issue new_element{description, status, reporter, solver};
        this->issues.push_back(new_element);

    }
    fin.close();
}