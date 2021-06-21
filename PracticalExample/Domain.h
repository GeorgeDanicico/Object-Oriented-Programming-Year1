//
// Created by georg on 6/21/2021.
//

#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class User{
private:
    string name, type;
public:
    User():name{""}, type{""}{}
    User(string name, string type) : name{name}, type{type}{}
    string getName() const {return name;}
    string getType() const {return type;}
    ~User()=default;
};

class Issue{
private:
    string description;
    string status;
    string reporter;
    string solver;

public:
    Issue(string description, string status, string reporter, string solver):description{description}, status{status},reporter{reporter},solver{solver}{}
    string getDescription() const { return description;}
    string getStatus() const { return status;}
    string getReporter() const { return reporter;}
    string getSolver() const { return solver;}
    void setStatus(string new_status){ status = std::move(new_status);}
    void setReporter(string new_reporter){ reporter = std::move(new_reporter);}
    void setSolver(string new_solver){ solver = std::move(new_solver);}

    ~Issue() = default;
};
