//
// Created by georg on 5/25/2021.
//

#pragma once
#include "repo.h"

class Operation{
public:
    virtual void undo()=0;
    virtual void redo()=0;
};
