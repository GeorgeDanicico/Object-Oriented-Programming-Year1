#include "tests.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
int increasing1(char* string1, char* string2) {
	if (strcmp(string1, string2) > 0)
		return 1;
	return 0;
}

void testMedicine() {
	// Testing if it creates a medicine
	Medicine* medicine = createMedicine("Vidan", 12, 12, 12);
	assert(medicine->concentration == 12);
	assert(medicine->price == 12);
	assert(medicine->quantity == 12);
	assert(strcmp(medicine->name, "Vidan") == 0);

	// Testing the getters and the setters.
	assert(getQuantity(medicine) == 12);
	assert(getPrice(medicine) == 12);

	setPrice(medicine, 20);
	setQuantity(medicine, 30);

	assert(getQuantity(medicine) == 30);
	assert(getPrice(medicine) == 20);

	destroyMedicine(medicine);

}

void testDynamicArray() {
	DynamicArray* da = createDA(10);
	assert(da->current_length == 0);

	Medicine* medicine = createMedicine("Vidan", 12, 12, 12);
	TElem element = medicine;
	addElement(da, element);
	assert(da->current_length == 1);

	assert(searchIdentifiers(da, "Vidan", 12) == 0);

	Medicine* medicine1 = createMedicine("Vidan", 12, 30, 12);
	TElem new_elem = medicine1;
	updateElement(da, new_elem, 0);

	element = getElem(da, 0);
	assert(element == medicine1);

	resizeDA(da);
	assert(da->capacity == 20);

	destroyDA(da);

}

void testRepository() {
	Repo* repo = createRepo();
	Medicine* medicine1 = createMedicine("Vidan", 12, 12, 12);
	Medicine* medicine2 = createMedicine("Vin", 12, 12, 12);
	Medicine* medicine3 = createMedicine("Rachiu", 12, 12, 12);
	Medicine* medicine4 = createMedicine("Palinca", 12, 12, 12);
	Medicine* medicine5 = createMedicine("Vidan", 12, 20, 12);

	assert(addRepo(repo, medicine1) == 1);
	assert(addRepo(repo, medicine2) == 1);
	assert(addRepo(repo, medicine3) == 1);
	assert(addRepo(repo, medicine4) == 1);
	assert(addRepo(repo, medicine5) == 1);

	assert(deleteFromRepo(repo, 2) == 1);
	assert(deleteFromRepo(repo, 12) == -1);

	Medicine* new_medicine = createMedicine("Vidan", 12, 12, 12);

	updateRepo(repo, new_medicine, 0, 1, 300);
	assert(repo->da->medicines[0]->quantity == 300);

	DynamicArray* da2 = getRepoElements(repo);
	assert(getArraySize(da2) == 3);
	free(da2->medicines);
	free(da2);

	assert(getRepoSize(repo) == 3);
	destroyRepo(repo);
}

void testService() {
	Undo* undo = createUndo();
	Redo* redo = createRedo();
	Repo* repo = createRepo();
	Service* service = createService(repo);
	
	assert(addServiceElem(service, "vidan", 12, 12, 12), 1);
	assert(addServiceElem(service, "vidan", 12, 12, 12), 1);

	assert(getQuantity(getElem(service->repo->da, 0)) == 24);
	
	assert(addServiceElem(service, "aulin", 12, 12, 12), 1);
	assert(addServiceElem(service, "para", 12, 12, 12), 1);
	assert(addServiceElem(service, "dada", 12, 12, 12), 1);
	assert(addServiceElem(service, "bada", 12, 12, 12), 1);
	assert(addServiceElem(service, "gada", 12, 12, 12), 1);
	assert(addServiceElem(service, "rada", 12, 12, 12), 1);
	assert(addServiceElem(service, "hada", 12, 12, 12), 1);
	assert(addServiceElem(service, "fada", 12, 12, 12), 1);
	assert(addServiceElem(service, "cada", 12, 12, 12), 1);
	assert(deleteServiceElem(service, "aulin", 12) == 1);
	assert(deleteServiceElem(service, "aulin", 12) == -1);

	assert(updateServiceElem(service, "dada", 12,1,200) == 1);
	assert(updateServiceElem(service, "dada", 12, 1, -20) == -1);

	int index = 0;
	char empty[10] = "";

	DynamicArray* da2 = sortByName(listAllMedicinesFilter(service, empty), increasing1);
	assert(da2->current_length == 9);

	assert(strcmp(da2->medicines[0]->name, "bada") == 0);

	free(da2->medicines);
	free(da2);
	
	destroyService(service);
	destroyRedo(redo);
	destroyUndo(undo);
}

void testStack() {
	Undo* undo = createUndo();
	Redo* redo = createRedo();
	stack* stack = createStack(10);

	Repo* repo = createRepo();
	Service* service = createService(repo);
	assert(addServiceElem(service, "aulin", 12, 12, 12), 1);
	assert(addServiceElem(service, "para", 12, 12, 12), 1);
	assert(addServiceElem(service, "dada", 12, 12, 12), 1);
	assert(addServiceElem(service, "bada", 12, 12, 12), 1);

	Service* copy = deepCopyService(service);
	addNewFrame(stack, copy);

	assert(deleteServiceElem(service, "aulin", 12) == 1);
	Service* copy1 = deepCopyService(service);
	addNewFrame(stack, copy1);
	assert(stack->savedStacks == 2);
	assert(deleteServiceElem(stack->service[1], "aulin", 12) == -1);
	deleteFrame(stack);
	assert(stack->savedStacks == 1);
	assert(deleteServiceElem(stack->service[0], "aulin", 12) == 1);

	destroyService(service);
	destroyStack(stack);
	destroyRedo(redo);
	destroyUndo(undo);
}

void testUndoRedo() {

	Undo* undo = createUndo();
	Redo* redo = createRedo();

	Repo* repo = createRepo();
	Service* service = createService(repo);

	assert(addServiceElem(service, "aulin", 12, 12, 12), 1);

	Service* copie = undoStep(undo, redo, service);
	if (copie != NULL)
		service = copie;

	copie = redoStep(undo, redo, service);
	if (copie != NULL)
		service = copie;

	assert(addServiceElem(service, "aulin", 12, 12, 12), 1);
	assert(getQuantity(service->repo->da->medicines[0]) == 24);
	assert(addServiceElem(service, "para", 12, 12, 12), 1);
	assert(addServiceElem(service, "dada", 12, 12, 12), 1);
	assert(addServiceElem(service, "bada", 12, 12, 12), 1);

	destroyService(service);
	destroyRedo(redo);
	destroyUndo(undo);
}


void all_tests() {
	testMedicine();
	testDynamicArray();
	testRepository();
	testService();
	testStack();
	testUndoRedo();
	printf("Tested executed succesfully.\n");
}
