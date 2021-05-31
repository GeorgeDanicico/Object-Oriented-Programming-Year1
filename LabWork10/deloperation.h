//
// Created by georg on 5/25/2021.
//

#pragma once
#include "operation.h"


class delOp : public Operation{

private:
    IRepo<TElem>* repo;
    TElem ev;
public:
    delOp(IRepo<TElem>* r, TElem ev) : repo(r), ev(ev){}
    virtual void undo() override;
    virtual void redo() override;
    ~delOp()=default;
};

void delOp::undo(){
    this->repo->add(this->ev);
}

void delOp::redo(){
    this->repo->remove(this->ev);
}