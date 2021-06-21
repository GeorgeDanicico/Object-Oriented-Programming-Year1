//
// Created by georg on 6/21/2021.
//

#include "Repository.h"

Repo::Repo(string filename, string filename1, bool save):filename1{filename}, filename2{filename1}, save{save}{
    this->load_users();
    this->load_issues();
}

void Repo::save_stars() {
    ofstream fout(this->filename2);
    string line;
    vector<Star> v = stars;
    sort(v.begin(), v.end(), [this](Star& s1, Star& s2){
        return s1.getConstellation() > s2.getConstellation();
    });

    for(auto& elem : v){
        line.clear();
        line = line + elem.getName() + ";" + elem.getConstellation() + ";" + to_string(elem.getRA()) + ";" + to_string(elem.getDec()) + "\n";
        fout << line;
    }
    fout.close();
}

void Repo::save_astronomers() {
    ofstream fout(this->filename1);
    string line;
    for(auto& elem : this->astronomers){
        line.clear();
        line = line + elem.getName() + ";" + elem.getConstellation() + "\n";
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
        Astronomer new_element{name, type};
        this->astronomers.push_back(new_element);

    }
    fin.close();
}

void Repo::load_issues() {
    ifstream fin(this->filename2);
    string line;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, name, constellation, RA, Dec, diameter;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(name.empty())
                name = token;
            else if(constellation.empty())
                constellation = token;
            else if(RA.empty()){
                RA = token;
            }
            else Dec = token;

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        diameter = line;
        line.clear();
        int r = stoi(RA);int d = stoi(Dec); int dm = stoi(diameter);
        Star new_element{name, constellation, r, d, dm};
        this->stars.push_back(new_element);

    }
    fin.close();
}