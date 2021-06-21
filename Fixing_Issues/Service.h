//
// Created by georg on 6/21/2021.
//

#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Subject{
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}
    void add_user();
    bool add_issue(Issue i){
        /*
         * This function adds an Issue to the list.
         * The issues are uniquely identified by their description.
         * The issue will be added only if there are no others issues with the same description.
        */
        vector<Issue>& issues = this->getRepo().getIssues();
        for(auto& e : issues){
            if(e.getDescription() == i.getDescription())
                return false;
        }
        this->getRepo().add_issue(i);
        this->notify();

        return true;
    }
    bool remove_issue(string title){

        vector<Issue> issues = this->getRepo().getIssues();
        auto it = find_if(issues.begin(), issues.end(), [&](Issue& i1){
            return title == i1.getDescription();
        });

        if(it != issues.end()){
            this->getRepo().remove_issue(*it);
            this->notify();
            return true;
        }
        return false;
    }
    void modify(Issue i){
        /*
         * Gets an issue with the new status and the new programmer
         * The repository will deal with it further
         */
        this->repo.update(i);
        this->notify();
    }
    Repo& getRepo(){ return this->repo;}
    ~Service()=default;

};
