//
// Created by georg on 4/5/2021.
//

#include "Repo.h"

void Repository::addGene(TElem gene){
    this->Vector.push_back(gene);
}

string Repository::GetSequenceOfAnOrg(const string &org, const string &name) {
    for(auto element : this->Vector){
        if(element.GetName() == name && element.GetOrganism() == org)
            return element.GetSequence();
    }
    return "";
}
