//
// Created by georg on 6/21/2021.
//
#include "Repository.h"
#include "Observer.h"

class Service : public Subject{
private:
    Repo& repo;
public:
    Service(Repo& repo):repo{repo}{}
    //void add_user();
    bool add_star(Star s){
        /*
         * This function adds an Issue to the list.
         * The issues are uniquely identified by their description.
         * The issue will be added only if there are no others issues with the same description.
        */
        vector<Star>& stars = this->getRepo().getStars();
        for(auto& e : stars){
            if(e.getName() == s.getName())
                return false;
        }
        this->getRepo().add_star(s);
        this->notify();

        return true;
    }
    Star& find(string name){
        vector<Star>& stars = this->getRepo().getStars();
        auto it = find_if(stars.begin(), stars.end(), [&](Star& s){
            return s.getName() == name;
        });

        if(it != stars.end())
            return *it;

    }
//    bool remove_issue(string title){
//
//        vector<Issue> issues = this->getRepo().getIssues();
//        auto it = find_if(issues.begin(), issues.end(), [&](Issue& i1){
//            return title == i1.getDescription();
//        });
//
//        if(it != issues.end()){
//            this->getRepo().remove_issue(*it);
//            this->notify();
//            return true;
//        }
//        return false;
//    }
//    void modify(Issue i){
//        /*
//         * Gets an issue with the new status and the new programmer
//         * The repository will deal with it further
//         */
//        this->repo.update(i);
//        this->notify();
//    }
    Repo& getRepo(){ return this->repo;}
    ~Service()=default;

};
