#include "undo.h"
#include <stdio.h>


Undo* createUndo() {
	Undo* undo = malloc(sizeof(Undo));
	undo->stack = createStack(2);
	return undo;
}

Redo* createRedo() {
	Redo* redo = malloc(sizeof(Redo));
	redo->stack = createStack(2);
	redo->undosBefore = 0;
	return redo;
}

void destroyUndo(Undo* undo) {
	destroyStack(undo->stack);
	free(undo);
}

void destroyRedo(Redo* redo) {
	destroyStack(redo->stack);
	free(redo);
}

Redo* clearRedo(Redo* redo) {
	destroyRedo(redo);
	Redo* redo1 = createRedo();
}

Service* undoStep(Undo* undo, Redo* redo, Service* currentService) {

	// if there is no stack saved, you can't undo.
	if (undo->stack->savedStacks == 0)
		return NULL;

	// we make a copy so that we can attach it to the current service
	Service* copy_undo = deepCopyService(undo->stack->service[undo->stack->savedStacks - 1]);
	// the last stack in undo is deleted.
	deleteFrame(undo->stack);
	// we copy the current service because we are going to destroy it and attach the one from the undo.
	Service* copy_service = deepCopyService(currentService);
	addNewFrame(redo->stack, copy_service);
	redo->undosBefore++;

	destroyService(currentService);

	return copy_undo;
}	


Service* redoStep(Undo* undo, Redo* redo, Service* currentService) {
	if (redo->undosBefore == 0 || redo->stack->savedStacks == 0)
		return NULL;

	redo->undosBefore--;
	// we make a copy of the last service on the redo stack
	Service* copy_redo = deepCopyService(redo->stack->service[redo->stack->savedStacks - 1]);
	deleteFrame(redo->stack);
	Service* copy_service = deepCopyService(currentService);
	addNewFrame(undo->stack, copy_service);

	destroyService(currentService);
	return copy_redo;
}

