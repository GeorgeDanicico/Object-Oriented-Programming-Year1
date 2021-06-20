//
// Created by georg on 6/20/2021.
//

#pragma once
#include <vector>
#include <algorithm>
using namespace std;


class Observer{
public:
    virtual void update()=0;
    virtual ~Observer()=default;
};

class Subject{
private:
    vector<Observer*> observers;
public:
    virtual ~Subject()=default;
    void addObserver(Observer* obs){ this->observers.push_back(obs);}
    void removeObserver(Observer* obs){
        auto it = find(observers.begin(), observers.end(), obs);
        if(it != observers.end())
            observers.erase(it);
    }
    void notify(){
        for(auto obs:observers){
            obs->update();
        }
    }


};
