//
// Created by georg on 4/15/2021.
//

#pragma once
#include <vector>
#include "repo.h"

// This is the abstract class from which both the Store html and Store csv will inherit.
class Abstract_store {
protected:
    IRepo<TElem>* _storage;
public:
    // The function are pure virtual, meaning that in order to use them, the children classes will have to implement them.
    Abstract_store(IRepo<TElem>* storage): _storage{storage}{}
    virtual ~Abstract_store()=default;
    virtual void write()=0;
    virtual void open()=0;
};
