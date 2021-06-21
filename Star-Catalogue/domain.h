//
// Created by georg on 6/21/2021.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;


class Astronomer{
private:
    string name, constellation;
public:
    Astronomer(string name, string constellation) : name{name}, constellation{constellation}{}
    string getName() const { return name;}
    string getConstellation() const { return constellation;}
    ~Astronomer()=default;

};

class Star{
private:
    string name, constellation;
    int RA,Dec, diameter;
public:
    Star(string name, string constellation, int r, int d, int diameter):name{name}, constellation{constellation}, RA{r}, Dec{d}, diameter{diameter}{}
    string getName() const{ return name;}
    string getConstellation() const { return constellation;}
    int getRA() const {return RA;}
    int getDec() const {return Dec;}
    int getDiameter() const {return diameter;}
    ~Star()=default;
};
