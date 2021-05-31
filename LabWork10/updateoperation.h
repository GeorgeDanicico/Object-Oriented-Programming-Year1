//
// Created by georg on 5/25/2021.
//

#pragma once
#include "operation.h"


class updateOp : public Operation{
private:
    IRepo<TElem>* repo;
    TElem ev;
    TElem old;
    int position;
public:
    updateOp(IRepo<TElem>* r, TElem& ev, TElem& old, int &p) : repo(r), ev(ev), old(old), position(p){}
    virtual void undo() override;
    virtual void redo() override;
    ~updateOp()=default;
};

void updateOp::undo(){
    this->repo->update(old, position);
}

void updateOp::redo(){
    this->repo->update(ev, position);
}