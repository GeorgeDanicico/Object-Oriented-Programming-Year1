#pragma once
#include "repo.h"
#include <vector>
#include <algorithm>
#include "Exception.h"
#include <iostream>
#include <fstream>
#include "sqlite/sqlite3.h"

using namespace std;

template<typename T>
class Repo: public IRepo<T>{
private:
    string filename;

public:
    Repo(vector<T>& STLVector, const string& filename);
    ~Repo();
    virtual void add(const T& new_element) override;
    virtual void remove(const T& element) override;
    virtual void update(const T& new_element, int position) override;
    virtual bool search(const T& element) override;
    virtual vector<T>& get_all() override;
    virtual const TElem& get_element(int position) override;
    // non virtual functions, which means these are specific only for this class.
    void load();
    void save();
};

template<typename T>
void Repo<T>::add(const T& new_element){
    auto it = find(this->STLVector.begin(), this->STLVector.end(), new_element);
    if(it != this->STLVector.end()){
        throw ImplementedException("Element already in the repo.\n");
    }
    this->STLVector.push_back(new_element);
    if(!this->filename.empty())
        this->save();
}

template<typename T>
void Repo<T>::remove(const T &element) {
    auto it = find(this->STLVector.begin(), this->STLVector.end(), element);
    if(it == this->STLVector.end()){
        throw ImplementedException("The element does not exist.\n");
    }

    this->STLVector.erase(it);
    if(!this->filename.empty())
        this->save();
}

template<typename T>
void Repo<T>::update(const T &new_element, int position) {
    this->STLVector[position] = new_element;
    this->save();
}

template<typename T>
bool Repo<T>::search(const T &element) {
    auto it = find(this->STLVector.begin(), this->STLVector.end(), element);
    if (it == this->STLVector.end())
        return false;
    return true;
}

template<typename T>
vector<T> &Repo<T>::get_all() {
    return this->STLVector;
}

template<typename T>
const TElem &Repo<T>::get_element(int position) {
    return this->STLVector[position];
}

template<typename T>
Repo<T>::Repo(vector<T> &STLVector, const string &filename):IRepo<T>(STLVector), filename(filename) {
    if(!filename.empty()){
        this->load();
    }
}

template<typename T>
void Repo<T>::save() {
    ofstream fout(this->filename);
    string line;
    for(auto& elem : this->STLVector){
        line.clear();
        Date date = elem.getDate();
        line = line + elem.getTitle() + ";" + elem.getDescription() + ";";
        line = line + to_string(date.getHour()) + "/" + to_string(date.getMinutes()) + "/" + to_string(date.getDay()) +
               + "/" + to_string(date.getMonth()) + "/" + to_string(date.getYear()) + ";";
        line = line + to_string(elem.getPeopleNr()) + ";" + elem.getLink() + "\n";
        fout << line;
    }
    fout.close();
}

template<typename T>
void Repo<T>::load() {
    ifstream fin(this->filename);
    string line;
    int hour, minutes, day, month, year, peopleNumber;

    while(std::getline(fin, line)){
        size_t positions = 0;
        string token, title, description, link, people, date;
        positions = line.find(';');
        while(positions != string::npos){
            token = line.substr(0, positions);
            if(title.empty())
                title = token;
            else if(description.empty())
                description = token;
            else if(date.empty()){
                date = "ok";
                hour = stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                minutes = stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                day = stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                month = stoi(token.substr(0, token.find('/')));
                token.erase(0, token.find('/') + 1);
                year = stoi(token.substr(0, token.find(';')));
            }
            else if(people.empty()){
                people = "ok";
                peopleNumber = stoi(token);
            }

            line.erase(0, positions + 1);
            positions = line.find(';');
        }
        link = line;
        line.clear();
        Date date2{hour, minutes, day, month, year};
        T new_element{title, description, date2, peopleNumber, link};
        this->STLVector.push_back(new_element);

    }
    fin.close();
}

template<typename T>
Repo<T>::~Repo()=default;