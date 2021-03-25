#include <iostream>
#include <fstream>
#include "repo.h"

//Repository::Repository() {
//    DynamicVector<TElem> dv;
//    this->dynamicVector = dv;
//    this->file_name = "";
//}

Repository::Repository(DynamicVector<TElem>& dV ,const std::string& file_name):dynamicVector(dV) {
	this->file_name = file_name;
	if(!file_name.empty())
        this->loadFromFile();
}

//Repository::Repository(const Repository &repo) {
//        this->dynamicVector = repo.dynamicVector;
//        this->file_name = repo.file_name;
//}

Repository::~Repository()= default;

// We simply just add an element to the repo by calling the function from the DynamicVector class
void Repository::addRepoElement(const TElem& new_element) {
    this->dynamicVector.add(new_element);
	if(!this->file_name.empty())
	    this->saveToFile();
}

// We simply just delete an element from the repo by calling the function from the DynamicVector class
void Repository::deleteRepoElement(int position) {
    this->dynamicVector.remove(position);
    if(!this->file_name.empty())
        this->saveToFile();
}

// We simply just update an element from the repo by calling the function from the DynamicVector class
void Repository::updateRepoElement(const TElem& new_element, int position) {
    this->dynamicVector.updateEvent(new_element, position);
    if (!this->file_name.empty())
        this->saveToFile();
}

void Repository::loadFromFile() {
    std::ifstream fin(this->file_name);
    std::string line;
    int hour, minutes, day, month, year, peopleNumber;

    while(std::getline(fin, line)){
        size_t positions = 0;
        std::string token, title, description, link, people, date;
        positions = line.find(';');
        while(positions != std::string::npos){
            token = line.substr(0, positions);
            if(title.empty())
                title = token;
            else if(description.empty())
                description = token;
            else if(date.empty()){
                date = "ok";
                hour = std::stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                minutes = std::stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                day = std::stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                month = std::stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                year = std::stoi(token.substr(0, token.find(';')));
            }
            else if(people.empty()){
                people = "ok";
                peopleNumber = std::stoi(token);
            }

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        link = line;
        line.clear();
        Date date2{hour, minutes, day, month, year};
        TElem element{title, description, date2, peopleNumber, link};
        this->dynamicVector.add(element);

    }

    fin.close();

}

void Repository::saveToFile() {
std::ofstream fout(this->file_name);
std::string line;
for(int index = 0; index < this->getRepoSize(); index++){
    line.clear();
    Date date = this->getRepoElement(index).getDate();
    line = line + this->getRepoElement(index).getTitle() + ";" + this->getRepoElement(index).getDescription() + ";";
    line = line + std::to_string(date.getHour()) + "/" + std::to_string(date.getMinutes()) + "/" + std::to_string(date.getDay()) +
             + "/" + std::to_string(date.getMonth()) + "/" + std::to_string(date.getYear()) + ";";
    line = line + std::to_string(this->getRepoElement(index).getPeopleNr()) + ";" + this->getRepoElement(index).getLink() + "\n";
    fout << line;
}

fout.close();


}
