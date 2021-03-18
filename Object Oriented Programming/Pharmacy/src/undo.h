#pragma once
#include "stack.h"

typedef struct {
	stack* stack;
}Undo;

typedef struct {
	stack* stack;
	int undosBefore;
}Redo;

Redo* createRedo();
void destroyRedo(Redo* redo);
Service* redoStep(Undo* undo, Redo* redo, Service* currentService);
Service* undoStep(Undo* undo, Redo* redo, Service* currentService);
Redo* clearRedo(Redo* redo);
Undo* createUndo();
void destroyUndo(Undo* undo);