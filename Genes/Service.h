//
// Created by georg on 4/5/2021.
//
#pragma once
#include "Repo.h"

class Service {
private:
    Repository& repo;

public:
    explicit Service(Repository& repo):repo{repo}{}

    ~Service()=default;

    int GetServiceSize(){ return this->repo.GetRepoSize(); }

    vector<TElem> sortedGenes();

    vector<TElem> filteredGenes(const string& seq);

    bool checkIfOrganismExist(const string& org, const string& name);

    bool addNewGene(const string& organism, const string& name, const string& sequence);

    string longestCommSeq(const string& org1, const string& name1, const string& org2, const string& name2);
};

