//
// Created by georg on 6/20/2021.
//

#pragma once
#include <string>
#include <utility>
using namespace std;


class User{
private:
    string photo, name;
public:
    User(string uniq, string name) : photo{uniq}, name{name}{}
    string getPhoto() const { return this->photo;}
    string getName() const { return this->name;}
    ~User()=default;
};

class Message{
private:
    string message;
public:
    Message(string& message): message{message}{}
    string getMessage() const { return this->message;}
    ~Message()=default;
};
