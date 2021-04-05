//
// Created by georg on 4/5/2021.
//

#include "UI.h"
#include <iostream>

void ui::print_menu() {
    cout << "1. Add gene. \n";
    cout << "2. Show all genes. \n";
    cout << "3. Show all genes filtered by a given string.\n";
    cout << "4. Show longest common sequence of 2 pairs of organisms and names.\n";
    cout << "0. Exit. \n";
}

void ui::start_application() {

    while(true){
        this->print_menu();
        string command;
        cout << "Enter>>";
        getline(cin, command);

        if(command == "1")
            this->addUI();
        else if(command == "2")
            this->showUI();
        else if(command == "3")
            this->showFilteredUI();
        else if(command == "4")
            this->longestCommUI();
        else if(command == "0"){
            break;
        }
        else cout << "Invalid command.\n";
    }

}

void ui::addUI() {
    string organism, name, sequence;

    cout << "Enter the organism: ";
    getline(cin, organism);
    cout << "Enter the name: ";
    getline(cin, name);
    cout << "Enter the sequence: ";
    getline(cin, sequence);

    if(!this->service.addNewGene(organism, name, sequence))
    {
        cout <<"The same gene and organism already exist!\n\n";
        return;
    }
    else{
        cout <<"New organism added successfully.\n\n";
        return;
    }
}

void ui::showUI() {
    if (this->service.GetServiceSize() == 0){
        cout << "There are no genes registered.\n\n";
        return;
    }
    else{
        vector<TElem> copy = this->service.sortedGenes();
        for(auto gene : copy){
            cout.width(15); cout << left << gene.GetOrganism() << " | ";
            cout.width(15); cout << left << gene.GetName() << " | ";
            cout.width(25); cout << right << gene.GetSequence() << endl;
        }
    }
    cout << "\n";

}

void ui::showFilteredUI() {
    string seq;
    cout << "Enter the sequence>>";
    getline(cin, seq);

    vector<TElem> filtered;
    filtered = this->service.filteredGenes(seq);

    if (filtered.size() == 0){
        cout << "There are no genes that satisfy your condition.\n";
        return;
    }
    else{
        for(auto gene : filtered){
            cout.width(15); cout << left << gene.GetOrganism() << " | ";
            cout.width(15); cout << left << gene.GetName() << " | ";
            cout.width(25); cout << right << gene.GetSequence() << endl;
        }
    }
    cout << "\n";

}

void ui::longestCommUI() {
    string org1,org2,name1,name2;
    cout << "Enter the organism1>>";
    getline(cin, org1);
    cout << "Enter the name 1>>";
    getline(cin, name1);
    cout << "Enter the organism2>>";
    getline(cin, org2);
    cout << "Enter the name2>>";
    getline(cin, name2);

    if(!this->service.checkIfOrganismExist(org1, name1) || !this->service.checkIfOrganismExist(org2, name2))
    {
        cout << "Invalid genes given.\n";
        return;
    }

    string seq = this->service.longestCommSeq(org1, name1, org2, name2);
    cout << "The longest common sequence is: " << seq;
    cout << "\n\n";

}
