#include "stack.h"
#include <string.h>
#include <stdio.h>

stack* createStack(int capacity) {
	stack* Stack = malloc(sizeof(stack));

	Stack->service = (StackFrame*)malloc(capacity * sizeof(StackFrame));
	Stack->capacity = capacity;
	Stack->savedStacks = 0;

	return Stack;
}

void destroyStack(stack* stack) {

	int index = 0;
	for (index = 0; index < stack->savedStacks; index++)
		destroyService(stack->service[index]);

	free(stack->service);
	free(stack);
}

void resizeStack(stack* Stack) {
	Stack->capacity = 2 * Stack->capacity;
	StackFrame* newStack = (StackFrame*)malloc(Stack->capacity * sizeof(StackFrame));

	int index = 0;
	for (index = 0; index < Stack->savedStacks; index++) {
		newStack[index] = Stack->service[index];
	}
	free(Stack->service);
	Stack->service = newStack;
}

Service* deepCopyService(Service* service) {
	Repo* copy_repo = createRepo();
	Service* copy_service = createService(copy_repo);

	int index = 0;
	for (index = 0; index < getRepoSize(service->repo); index++) {
		TElem element = getElem(service->repo->da, index);
		addServiceElem(copy_service, element->name, element->concentration, element->quantity, element->price);
	}

	return copy_service;
}

void addNewFrame(stack* stack, Service* service) {
	if (stack->capacity == stack->savedStacks) {
		resizeStack(stack);
	}
	stack->service[stack->savedStacks] = service;
	stack->savedStacks += 1;
}

void deleteFrame(stack* stack) {
	stack->savedStacks -= 1;
	destroyService(stack->service[stack->savedStacks]);
}