//
// Created by georg on 6/20/2021.
//

#pragma once
#include "domain.h"

class Repo{
private:
    vector<Programmer> programmers;
    vector<SourceFile> sources;
    string filename1;
    string filename2;
public:
    Repo(string filename, string filename1);
    void add_programmer(Programmer element){
        programmers.push_back(element);
        //this->save_prog();
    }
    void add_source(SourceFile element) {
        sources.push_back(element);
        //this->save_sources();
    }

    vector<Programmer>& getProgrammers() { return programmers;}
    vector<SourceFile>& getSources() {return sources;}

    int size_sources() const {return this->sources.size();}
    SourceFile getFile(int pos) const {return this->sources[pos];}

    void save_prog();
    void save_sources();
    void load_prog();
    void load_sources();
    ~Repo()=default;
};


