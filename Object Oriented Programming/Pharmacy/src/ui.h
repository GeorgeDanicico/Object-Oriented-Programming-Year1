#pragma once

#include "service.h"
#include "stack.h"
#include "undo.h"


typedef struct {
	Service* service;
	Undo* undo;
	Redo* redo;
}UI;

UI* createUI(Service* service);
void destroyUI(UI* ui);

int checkCharNumber(char* string_number);
void print_menu();
void start(UI* ui);
void addMedicineUI(UI* ui, char input[]);
void listMedicineUI(UI* ui, char input[]);
void updateMedicineUI(UI* ui, char input[]);
void deleteMedicineUI(UI* ui, char input[]);
void listLessUI(UI* ui, char input[]);
void undoUI(UI* ui, char input[]);
void redoUI(UI* ui, char input[]);
void setEntries(UI* ui);