//
// Created by georg on 4/15/2021.
//

#pragma once
#include "store.h"

class Store_csv : public Abstract_store{
private:
    string filename;
public:
    Store_csv(IRepo<TElem>* v, const string& filename):Abstract_store{v}, filename{filename}{}
    virtual void write() override;
    virtual void open() override;
};
