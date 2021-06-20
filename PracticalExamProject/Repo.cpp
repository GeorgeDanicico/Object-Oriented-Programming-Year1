//
// Created by georg on 6/20/2021.
//

#include "Repo.h"

Repo::Repo(string filename, string filename1):filename1{filename}, filename2{filename1}{
    this->load_prog();
    this->load_sources();
}

void Repo::save_sources() {
    ofstream fout(this->filename2);
    string line;
    for(auto& elem : this->sources){
        line.clear();
        line = line + elem.getName() + ";" + elem.getStatus() + ";" + elem.getCreator() + ";" + elem.getReviser() + "\n";
        fout << line;
    }
    fout.close();
}

void Repo::save_prog() {
    ofstream fout(this->filename1);
    string line;
    for(auto& elem : this->programmers){
        line.clear();
        line = line + elem.getName() + ";" + to_string(elem.getRevised()) + ";" + to_string(elem.getMust()) + "\n";
        fout << line;
    }
    fout.close();
}

void Repo::load_prog() {
    ifstream fin(this->filename1);
    string line;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, name, rev, must;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(name.empty())
                name = token;
            else if(rev.empty())
                rev = token;
            else if(must.empty()){
                must = token;
            }

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        must = line;
        line.clear();
        int r = stoi(rev);
        int m = stoi(must);
        Programmer new_element{name, r, m};
        this->programmers.push_back(new_element);

    }
    fin.close();
}

void Repo::load_sources() {
    ifstream fin(this->filename2);
    string line;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, name, status, creator, reviser;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(name.empty())
                name = token;
            else if(status.empty())
                status = token;
            else if(creator.empty()){
                creator = token;
            }

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        reviser = line;
        line.clear();
        SourceFile new_element{name, status, creator, reviser};
        this->sources.push_back(new_element);

    }
    fin.close();
}

