//
// Created by georg on 4/3/2021.
//
#pragma once
#include<exception>
#include<string>
#include <utility>

using namespace std;

class ImplementedException : public exception{

private:
    string _msg;
public:
    ImplementedException(string  msg) : _msg(msg){}

    virtual const char* what() const noexcept override{
        return this->_msg.c_str();
    }

};