//
// Created by georg on 4/18/2021.
//

#pragma once
#include "repo.h"
#include "../../sqlite/sqlite3.h"

vector<TElem> Elements;

template<typename T>
class Data_Repo : public IRepo<T>{
private:
    string db_name;
public:
    Data_Repo(vector<T> &STLVector, const string& db_name);
    ~Data_Repo()=default;
    virtual void add(const T& new_element) override;
    virtual void remove(const T& element) override;
    virtual void update(const T& new_element, int position) override;
    virtual bool search(const T& element) override;
    virtual vector<T>& get_all() override;
    virtual const TElem& get_element(int position) override;

};

int callback(void* data, int argc, char** argv, char** azColName){

    if(argc > 0){
        string title{argv[0]};
        string description{argv[1]};
        string link{argv[2]};
        int people = stoi(argv[3]);
        string token = argv[4];
        int hour, minutes, day, month, year;
        hour = stoi(token.substr(0, token.find('/')));
        token.erase(0, token.find('/') + 1);
        minutes = stoi(token.substr(0, token.find('/')));
        token.erase(0, token.find('/') + 1);
        day = stoi(token.substr(0, token.find('/')));
        token.erase(0, token.find('/') + 1);
        month = stoi(token.substr(0, token.find('/')));
        token.erase(0, token.find('/') + 1);
        year = stoi(token.substr(0, token.find(';')));

        Date date{hour, minutes, day, month, year};
        TElem elem{title, description, date, people, link};
        (static_cast<vector<TElem>*>(data))->push_back(elem);
    }

    return 0;
}

template<typename T>
Data_Repo<T>::Data_Repo(vector<T> &STLVector, const string &db_name) : IRepo<T>{STLVector}, db_name{db_name}{
    string command = "SELECT * FROM Events";

    int rc;
    sqlite3 *db;
    char* messageError;
    rc = sqlite3_open(this->db_name.c_str(), &db);
    if(rc)
        throw ImplementedException("The database couldn't be opened.\n");

    sqlite3_exec(db, command.c_str(), callback, &this->STLVector, &messageError);
    sqlite3_close(db);
}

template<typename T>
void Data_Repo<T>::add(const T &new_element) {
    auto it = find(this->STLVector.begin(), this->STLVector.end(), new_element);
    if(it != this->STLVector.end()){
        throw ImplementedException("Element already in the repo.\n");
    }
    this->STLVector.push_back(new_element);

    // connection to the data base
    string command = "INSERT INTO Events VALUES ('"+ new_element.getTitle() + "','" + new_element.getDescription() + "','" + new_element.getLink() + "','" + to_string(new_element.getPeopleNr()) + "','" + new_element.getDate().toString() + "');";
    int rc;
    sqlite3 *db;
    char* messageError;
    rc = sqlite3_open(db_name.c_str(), &db);
    if(rc)
        throw ImplementedException("The database couldn't be opened.\n");
    rc = sqlite3_exec(db, command.c_str(), NULL, 0, &messageError);
    if(rc != SQLITE_OK)
        throw ImplementedException("The operation couldn't be finished.\n");
    sqlite3_close(db);
}

template<typename T>
void Data_Repo<T>::remove(const T &element) {
    auto it = find(this->STLVector.begin(), this->STLVector.end(), element);
    if(it == this->STLVector.end()){
        throw ImplementedException("The element does not exist.\n");
    }

    this->STLVector.erase(it);

    // connection to the data base
    string command = "DELETE FROM Events WHERE Title = '"+ element.getTitle() + "';";
    int rc;
    sqlite3 *db;
    char* messageError;
    rc = sqlite3_open(db_name.c_str(), &db);
    if(rc)
        throw ImplementedException("The database couldn't be opened.\n");
    rc = sqlite3_exec(db, command.c_str(), NULL, 0, &messageError);
    if(rc != SQLITE_OK)
        throw ImplementedException("The operation couldn't be finished.\n");
    sqlite3_close(db);

}

template<typename T>
void Data_Repo<T>::update(const T &new_element, int position) {
    this->STLVector[position] = new_element;

    // connection to the data base
    string command = "UPDATE Events SET People= '"+ to_string(new_element.getPeopleNr()) + "',Date='" + new_element.getDate().toString()+ "' WHERE Title='" + new_element.getTitle() + "';";
    int rc;
    sqlite3 *db;
    char* messageError;
    rc = sqlite3_open(db_name.c_str(), &db);
    if(rc)
        throw ImplementedException("The database couldn't be opened.\n");
    rc = sqlite3_exec(db, command.c_str(), NULL, 0, &messageError);
    if(rc != SQLITE_OK)
        throw ImplementedException("The operation couldn't be finished.\n");
    sqlite3_close(db);
}

template<typename T>
bool Data_Repo<T>::search(const T &element) {
    auto it = find(this->STLVector.begin(), this->STLVector.end(), element);
    if (it == this->STLVector.end())
        return false;
    return true;
}

template<typename T>
vector<T> &Data_Repo<T>::get_all() {
    return this->STLVector;
}

template<typename T>
const TElem &Data_Repo<T>::get_element(int position) {
    return this->STLVector[position];
}