//
// Created by georg on 4/5/2021.
//
#pragma once
#include <string>
#include <iostream>
using namespace std;


class Gene{

private:
    string organism;
    string name;
    string sequence;
public:
    Gene(const string& organism, const string& name, const string& sequence);

    ~Gene()=default;

    int GetSequenceLength(){ return this->sequence.size();}

    string& GetOrganism(){ return this->organism;}

    string& GetName(){ return this->name; }

    string& GetSequence(){ return this->sequence; }

//    friend ostream& operator<<(std::ostream& os, const Gene& g);

};


