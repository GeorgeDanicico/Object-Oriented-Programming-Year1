//
// Created by georg on 5/25/2021.
//

#pragma once
#include "operation.h"


class addOp : public Operation{
private:
    IRepo<TElem>* r;
    TElem ev;

public:
    addOp(IRepo<TElem>* r, TElem ev) : r(r), ev(ev){}
    virtual void undo() override;
    virtual void redo() override;
    ~addOp()=default;
};

void addOp::undo(){
    this->r->remove(this->ev);
}

void addOp::redo(){
    this->r->add(this->ev);
}