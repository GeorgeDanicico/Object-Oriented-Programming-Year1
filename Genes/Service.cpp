//
// Created by georg on 4/5/2021.
//

#include "Service.h"
#include <algorithm>

bool Service::addNewGene(const string& organism, const string& name, const string& sequence){
    /*
     * This function will take as parameters an organism, a name and a sequence. It will create the Gene object
     * if it is a all the parameters are not empty. After, it will check if the Gene with the same organism and name has already
     * been registered. If it was, the function will return false
     */
    if(organism.empty() || name.empty() || sequence.empty())
        return false;

    TElem element{organism, name, sequence};

    vector<TElem> copy = this->repo.getElements();

    if(this->checkIfOrganismExist(organism, name))
        return false;

    this->repo.addGene(element);
    return true;
}

bool comparison(TElem e1, TElem e2){
    /*
     * This function represents the criteria for the sorting method from STL
     */
    return e1.GetSequenceLength() > e2.GetSequenceLength();
}

vector<TElem> Service::sortedGenes() {
    vector<TElem> copy = this->repo.getElements();

    sort(copy.begin(), copy.end(), comparison);
    return copy;
}

vector<TElem> Service::filteredGenes(const string& seq) {

    vector<TElem> sorted = this->sortedGenes();
    vector<TElem> copy;
    for(auto it = sorted.begin(); it < sorted.end(); it++)
        if((*it).GetSequence().find(seq) != string::npos)
            copy.push_back(*it);
    return copy;
}

bool Service::checkIfOrganismExist(const string &org, const string &name) {
    vector<TElem> copy = this->repo.getElements();

    for(auto el : copy){
        if(el.GetName() == name && el.GetOrganism() == org)
            return true;
    }
    return false;
}

string Service::longestCommSeq(const string& org1, const string& name1, const string& org2, const string& name2) {
    /*
     * org1 -> the first organism | name1 -> the name of the first gene.
     * org2 -> the second organism | name2 -> the name of the second gene.
     * We are going to find the longest contiguous common sequence of the given genes sequences.
     */

    string sequence1 = this->repo.GetSequenceOfAnOrg(org1, name1);
    string sequence2 = this->repo.GetSequenceOfAnOrg(org2, name2);

    string lcs;
    int max_length = 0;
    for(int index1 = 0; index1 < sequence1.size(); index1++){

        for(int index2 = index1; index2 < sequence1.size(); index2++) {
            char buffer[20];
            size_t length = sequence1.copy(buffer, index2 - index1 + 1, index1);
            buffer[length] = '\0';
            string checker{buffer};
            if(sequence2.find(checker) != string::npos){
                if(checker.size() > max_length)
                    max_length = checker.size(), lcs = checker;
            }
        }
    }

    return lcs;
}
