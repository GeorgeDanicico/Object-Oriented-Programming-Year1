#pragma once

#include "domain.h"
#include "dynamicArray.h"

typedef struct {
	DynamicArray* da;
}Repo;

Repo* createRepo();
void destroyRepo(Repo* repo);
int addRepo(Repo* repo, TElem element);
int deleteFromRepo(Repo* repo, int position);
void updateRepo(Repo* repo, TElem element, int position, int field, int value);
DynamicArray* getRepoElements(Repo* repo);
int getRepoSize(Repo* repo);