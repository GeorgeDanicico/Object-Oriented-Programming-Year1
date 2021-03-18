#pragma once


#include "repo.h"
typedef int(*Relation)(char*, char*);
typedef struct {
	Repo* repo;
}Service;


Service* createService(Repo* repo);
void destroyService(Service* service);
int addServiceElem(Service* service, char* name, int concentration, int quantity, int price);
int deleteServiceElem(Service* service, char* name, int concentration);
int updateServiceElem(Service* service, char* name, int concentration, int field, int value);
DynamicArray* sortByName(DynamicArray* da, Relation r);
DynamicArray* sortByConcetration(DynamicArray* da);
DynamicArray* listAllMedicinesFilter(Service* service, char* filter_string);
DynamicArray* filterMedicines(Service* service, int field, int value);
