//
// Created by georg on 6/20/2021.
//
#pragma once
#include "Repo.h"
#include "Observer.h"

class Service : public Subject{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo{repo}{}
    bool add_file(SourceFile file){
        vector<SourceFile> v = this->getRepo().getSources();
        for(auto& f : v){
            if(f.getName() == file.getName())
                return false;
        }
        this->repo.add_source(file);
        this->notify();
        return true;
    }

    void modify(SourceFile obj, Programmer &p){
        vector<SourceFile>& v = this->getRepo().getSources();
        for(auto& e : v){
            if(e.getName() == obj.getName()){
                e.setStatus("revised");
                e.setReviser(p.getName());
                break;
            }
        }
        p.revise();

        this->notify();
    };
    Repo& getRepo() { return repo;}
    ~Service()=default;
};



