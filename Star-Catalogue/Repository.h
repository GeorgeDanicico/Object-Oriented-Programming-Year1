//
// Created by georg on 6/21/2021.
//

#pragma once
#include "domain.h"

class Repo {
private:
    vector<Astronomer> astronomers;
    vector<Star> stars;
    bool save;
    string filename1;
    string filename2;
public:
    Repo(string filename, string filename1, bool save=false);
    void add_user(Astronomer element){
        astronomers.push_back(element);
        if(save)
            this->save_astronomers();
    }
    void add_star(Star element) {
        stars.push_back(element);
        if(save)
            this->save_stars();
    }

//    void remove_issue(Issue i){
//        auto it = find_if(stars.begin(), stars.end(), [&](Issue& i1){
//            return i.getDescription() == i1.getDescription();
//        });
//        if(it != stars.end())
//            stars.erase(it);
//        if(save)
//            this->save_stars();
//    }
//
//    void update(Issue i){
//        //  the element will be searched in the list by reference
//        // and when it will be found, it will be updated with the coresponding solver name
//        // and status;
//        for(auto& e : stars){
//            if(e.getDescription() == i.getDescription()){
//                e.setStatus(i.getStatus());
//                e.setSolver(i.getSolver());
//            }
//        }
//        if(save)
//            this->save_stars();
//    }

    vector<Astronomer>& getAstronomers() { return astronomers;}
    vector<Star>& getStars() {return stars;}

    int size_stars() const {return this->stars.size();}
    Star getStar(int pos) const {return this->stars[pos];}

    void save_astronomers();
    void save_stars();
    void load_users();
    void load_issues();
    ~Repo()=default;
};


