#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increasing(char* string1, char* string2) {
	if (strcmp(string1, string2) > 0)
		return 1;
	return 0;
}
int decreasing(char* string1, char* string2) {
	if (strcmp(string1, string2) < 0)
		return 1;
	return 0;
}

UI* createUI(Service* service)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;

	ui->undo = createUndo();
	ui->redo = createRedo();
	ui->service = service;
	return ui;
}

int checkCharNumber(char* string_number) {
	// This function checks if a given string is a number or not
	int length = strlen(string_number);
	int index, number = 0;
	for (index = 0; index < length; index++) {
		if (string_number[index] < '0' || string_number[index] > '9')
			return -1;
		number = number * 10 + (string_number[index] - '0');
	}
	return number;
}

void destroyUI(UI* ui)
{
	destroyRedo(ui->redo);
	destroyUndo(ui->undo);
	destroyService(ui->service);
	free(ui);
}

void print_menu()
{
	printf("- add name,concentration,quantity,price -> to add a medicine.\n");
	printf("- update name,concentration,field,value -> to update a medicine.\n");
	printf("- delete name,concentration -> delete a medicine by name/concetration.\n");
	printf("- list <string> -> to list all medicines that contains a string.\n");
	printf("- see <field> <value> -> to list all the medicines whose 'field' value is less than 'value'.\n");
	printf("- undo -> to undo the last operation that modified the data.\n");
	printf("- redo -> to redo the last operation that modified the data.\n");
	printf("- exit -> to exit the program.\n");
	printf("\n");
}

void start(UI* ui) {

	char input[200] = "";
	char copyinput[200] = ""; // after strtok, the input will be gone

	while (1) {

		print_menu();
		printf("Enter the command please>>");
		fgets(input, sizeof input, stdin);

		input[strcspn(input, "\n")] = 0;

		if (!strcmp(input, "exit")) {
			printf("Exiting...");
			break;
		}
		strcpy(copyinput, input);
		char* comm = strtok(input, " ");
		if (comm == NULL) {
			printf("Try again...\n");
			continue;
		}
		if (!strcmp(comm, "add"))
			addMedicineUI(ui, copyinput);
		else
			if (!strcmp(comm, "delete"))
				deleteMedicineUI(ui, copyinput);
			else
				if (!strcmp(comm, "update"))
					updateMedicineUI(ui, copyinput);
				else
					if (!strcmp(comm, "list"))
						listMedicineUI(ui, copyinput);
					else 
						if (!strcmp(comm, "see"))
							listLessUI(ui, copyinput);
						else
							if (!strcmp(comm, "undo"))
								undoUI(ui, copyinput);
							else
								if (!strcmp(comm, "redo"))
									redoUI(ui, copyinput);
					else printf("Invalid command... try again!.\n");
	}

}

void addMedicineUI(UI* ui, char input[]) {
	char* comm = strtok(input, " ");
	char* name = strtok(NULL, ", /");
	if (name == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* concentration = strtok(NULL, ", /");
	if (concentration == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* quantity = strtok(NULL, ", /");
	if (quantity == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* price = strtok(NULL, ", /");
	if (price == NULL) {
		printf("Invalid parameters.\n");
		return;
	}

	int conc = checkCharNumber(concentration);
	int quan = checkCharNumber(quantity);
	int pric = checkCharNumber(price);
	if (conc == -1 || quan == -1 || pric == -1) {
		printf("Invalid parameters...\n");
		return;
	}
	
	Service* copy = deepCopyService(ui->service);
	addNewFrame(ui->undo->stack, copy);
	if (addServiceElem(ui->service, name, conc, quan, pric) == 1)
	{
		copy = deepCopyService(ui->service);
		addNewFrame(ui->redo->stack, copy);
		printf("Succes!\n");
		ui->redo->undosBefore = 0;
	}
	else printf("Error.\n");
	
}

void listMedicineUI(UI* ui, char input[]) {
	char* filtering;
	char empty[10] = "", mode[20];
	printf("Enter the sorting type: ");
	fgets(mode, 20, stdin);
	filtering = empty;
	char* comm = strtok(input, ", /");
	char* test_filtering = strtok(NULL, ", /");
	if (test_filtering != NULL) {
		filtering = test_filtering;
	}
	DynamicArray* da2;

	mode[strcspn(mode, "\n")] = 0;
	int MODE = checkCharNumber(mode);
	if (MODE == -1 || (MODE != 1 && MODE != 2)) {
		printf("Invalid parameters...\n");
		return;
	}
	if (MODE == 1) {
		printf("Enter the type of sorting(ascending/descending): ");
		fgets(mode, 20, stdin);
		mode[strcspn(mode, "\n")] = 0;
		if(!strcmp(mode, "ascending"))
			da2 = sortByName(listAllMedicinesFilter(ui->service, filtering),increasing);
		else if(!strcmp(mode, "descending"))
			da2 = sortByName(listAllMedicinesFilter(ui->service, filtering), decreasing);
		else {
			printf("Invalid parameters.\n");
			return;
		}
	}
	else
		da2 = sortByConcetration(listAllMedicinesFilter(ui->service, filtering));
	printf("Listing...\n");

	int index = 0;
	if (getArraySize(da2) == 0) {
		printf("There are no elements matching the string.\n");
	}else
		for (index = 0; index < getArraySize(da2); index++) {
			printf("Medicine %d, Name: %s, Concentration: %d, Quantity: %d, Price: %d \n", index, da2->medicines[index]->name, da2->medicines[index]->concentration, da2->medicines[index]->quantity, da2->medicines[index]->price);
		}
	free(da2->medicines);
	free(da2);
	
}

void updateMedicineUI(UI* ui, char input[]) {
	char* command = strtok(input, " ");
	char* name = strtok(NULL, ", /");
	if (name == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* concentration = strtok(NULL, ", /");
	if (concentration == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* field = strtok(NULL, ", /");
	if (field == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* value = strtok(NULL, ", /");
	if (value == NULL) {
		printf("Invalid parameters.\n");
		return;
	}

	int conc = checkCharNumber(concentration);
	int val = checkCharNumber(value);
	if (conc == -1 || val == -1) {
		printf("Invalid parameters...\n");
		return;
	}
	int field_value = 0;
	if (strcmp(field, "quantity") == 0)
		field_value = 1;
	else if (strcmp(field, "price") == 0)
		field_value = 2;

	if (field_value == 0) {
		printf("Invalid input...\n");
		return;
	}

	Service* copy = deepCopyService(ui->service);
	addNewFrame(ui->undo->stack, copy);
	if (updateServiceElem(ui->service, name, conc, 1, val) == 1) {
		printf("Updated succesfully.\n");
		copy = deepCopyService(ui->service);
		addNewFrame(ui->redo->stack, copy);
		ui->redo->undosBefore = 0;
	}
	else {
		printf("Failed to update.\n");
		deleteFrame(ui->undo->stack);
	}
}

void deleteMedicineUI(UI* ui, char input[]) {
	char* command = strtok(input, " ");
	char* name = strtok(NULL, ",");
	if (name == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* concentration = strtok(NULL, ",");
	if (concentration == NULL) {
		printf("Invalid parameters.\n");
		return;
	}

	int conc = checkCharNumber(concentration);
	if (conc == -1) {
		printf("Invalid parameters...\n");
		return;
	}

	Service* copy = deepCopyService(ui->service);
	addNewFrame(ui->undo->stack, copy);
	if (deleteServiceElem(ui->service, name, conc) == 1) {
		copy = deepCopyService(ui->service);
		addNewFrame(ui->redo->stack, copy); 
		ui->redo->undosBefore = 0;
		printf("Deleted succesfully.\n");
	}
	else
	{
		printf("Failed to delete.\n");
		deleteFrame(ui->undo->stack);
	}
}

void listLessUI(UI* ui, char input[]) {
	char* command = strtok(input, " ");
	char* field = strtok(NULL, ",");
	if (field == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	char* value = strtok(NULL, " ");
	if (value == NULL) {
		printf("Invalid parameters.\n");
		return;
	}
	int Field = 0;
	if (!strcmp(field, "price")) {
		Field = 2;
	}
	else if (!strcmp(field, "quantity")) {
		Field = 1;
	}
	if (Field == 0) {
		printf("Invalid parameters.\n");
		return;
	}
	int val = checkCharNumber(value), index = 0;
	if (val == -1) {
		printf("Invalid parameters...\n");
		return;
	}

	DynamicArray* da2 = filterMedicines(ui->service, Field, val);
	if (getArraySize(da2) == 0) {
		printf("There are no elements in the field with the required value or less.\n");
	}
	else
		for (index = 0; index < getArraySize(da2); index++) {
			printf("Medicine %d, Name: %s, Concentration: %d, Quantity: %d, Price: %d \n", index, da2->medicines[index]->name, da2->medicines[index]->concentration, da2->medicines[index]->quantity, da2->medicines[index]->price);
		}
	free(da2->medicines);
	free(da2);
}

void undoUI(UI* ui, char input[]) {
	Service* copy = undoStep(ui->undo, ui->redo, ui->service);
	if (copy == NULL) {
		printf("You can't undo anymore.\n");
	}
	else {
		printf("Undo succesfully.\n");
		ui->service = copy;
	}
}

void redoUI(UI* ui, char input[]) {
	Service* copy = redoStep(ui->undo, ui->redo, ui->service);
	if (copy == NULL) {
		printf("You can't undo anymore.\n");
	}
	else {
		printf("Redo succesfully.\n");
		ui->service = copy;
	}
}

void setEntries(UI* ui) {
	char name[30] = "Paracetamol";
	int concentration = 50, quantity = 12, price = 28;
	addServiceElem(ui->service, name, concentration, quantity, price);
	
	strcpy(name, "Nurofen");
	concentration = 70, quantity = 10, price = 58;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Ibuprofen");
	concentration = 99, quantity = 20, price = 18;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Vitamina C");
	concentration = 47, quantity = 22, price = 30;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Diclofenac");
	concentration = 20, quantity = 2, price = 40;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Singulaire");
	concentration = 17, quantity = 32, price = 28;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Ulei canepa");
	concentration = 10, quantity = 12, price = 28;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Puterea ursu.");
	concentration = 70, quantity = 92, price = 98;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Algocamin");
	concentration = 30, quantity = 10, price = 38;
	addServiceElem(ui->service, name, concentration, quantity, price);

	strcpy(name, "Aulin");
	concentration = 30, quantity = 120, price = 18;
	addServiceElem(ui->service, name, concentration, quantity, price);

}