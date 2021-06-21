//
// Created by georg on 6/21/2021.
//
#pragma once
#include "Domain.h"

class Repo {
private:
    vector<User> users;
    vector<Issue> issues;
    bool save;
    string filename1;
    string filename2;
public:
    Repo(string filename, string filename1, bool save=false);
    void add_user(User element){
        users.push_back(element);
        if(save)
            this->save_users();
    }
    void add_issue(Issue element) {
        issues.push_back(element);
        if(save)
            this->save_issues();
    }

    void remove_issue(Issue i){
        auto it = find_if(issues.begin(), issues.end(), [&](Issue& i1){
            return i.getDescription() == i1.getDescription();
        });
        if(it != issues.end())
            issues.erase(it);
        if(save)
            this->save_issues();
    }

    void update(Issue i){
        //  the element will be searched in the list by reference
        // and when it will be found, it will be updated with the coresponding solver name
        // and status;
        for(auto& e : issues){
            if(e.getDescription() == i.getDescription()){
                e.setStatus(i.getStatus());
                e.setSolver(i.getSolver());
            }
        }
        if(save)
            this->save_issues();
    }

    vector<User>& getUsers() { return users;}
    vector<Issue>& getIssues() {return issues;}

    int size_issues() const {return this->issues.size();}
    Issue getFile(int pos) const {return this->issues[pos];}

    void save_users();
    void save_issues();
    void load_users();
    void load_issues();
    ~Repo()=default;
};


