//
// Created by georg on 4/5/2021.
//
#pragma once
#include "domain.h"
#include <vector>

typedef Gene TElem;

class Repository {
private:
    vector<TElem>& Vector;

public:
    explicit Repository(vector<TElem>& Vector):Vector{Vector}{}

    ~Repository()=default;

    int GetRepoSize(){ return this->Vector.size(); }

    string GetSequenceOfAnOrg(const string& org, const string& name);

    void addGene(TElem gene);

    vector<TElem> getElements(){return this->Vector; }
};


