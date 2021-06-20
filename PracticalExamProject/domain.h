//
// Created by georg on 6/20/2021.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Programmer {
private:
    string name;
    int revisedFiles;
    int mustRevise;
public:
    Programmer(string& name, int r, int m):name{name}, revisedFiles{r}, mustRevise{m}{}
    string getName() const {return name;}
    int getRevised() const {return revisedFiles;}
    int getMust() const {return mustRevise;}
    void revise() {this->revisedFiles = this->revisedFiles + 1;}
    ~Programmer()=default;

};

class SourceFile{
private:
    string name;
    string status;
    string creator;
    string reviser;
public:
    SourceFile(string& name, string status,string creator, string reviser):name{name}, status{status}, creator{creator}, reviser{reviser}{}
    string getName() const {return name;}
    string getReviser() const {return reviser;}
    string getCreator() const {return creator;}
    void setReviser(string newReviser) { this->reviser = newReviser;}
    void setStatus(string status){ this->status = status;}
    string getStatus() const {return status;}
    ~SourceFile()=default;
};


