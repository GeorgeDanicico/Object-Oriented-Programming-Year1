#pragma once
#include "service.h"

typedef Service* StackFrame;

typedef struct {
	StackFrame* service;
	int savedStacks;
	int capacity;
}stack;

stack* createStack(int capacity);
void destroyStack(stack* stack);
void resizeStack(stack* Stack);
Service* deepCopyService(Service* service);
void addNewFrame(stack* stack, Service* service);
void deleteFrame(stack* stack);