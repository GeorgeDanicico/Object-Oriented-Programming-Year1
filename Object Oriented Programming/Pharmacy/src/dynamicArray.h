#pragma once
#include "domain.h"

typedef Medicine* TElem;

typedef struct {
	TElem* medicines;
	int current_length;
	int capacity;
}DynamicArray;

DynamicArray* createDA(int capacity);
void destroyDA(DynamicArray* da);
void resizeDA(DynamicArray* da);

void addElement(DynamicArray* da, TElem element);
int searchIdentifiers(DynamicArray* da, char* identifier1, int identifier2);
void deleteElement(DynamicArray* da, int position);
void updateElement(DynamicArray* da, TElem new_elem, int position);
int getArraySize(DynamicArray* da);
TElem getElem(DynamicArray* da, int position);
