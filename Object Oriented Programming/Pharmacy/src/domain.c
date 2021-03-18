
#define _CRT_SECURE_NO_WARNINGS
#include "domain.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


Medicine* createMedicine(char* name, int concentration, int quantity, int price) {
	/// <summary>
	/// Creation of a medicine.
	/// </summary>
	/// <param name="name"> the name of the medicine.</param>
	/// <param name="concentration"> the concentration of the medicine.</param>
	/// <param name="quantity"> the quantity of the medicine.</param>
	/// <param name="price"> the price of the medicine.</param>
	/// <returns></returns>
	
	Medicine* medicine = (Medicine*)malloc(sizeof(Medicine));
	// Check if there was memory allocated
	if (medicine == NULL)
		return NULL;

	medicine->name = (char*)malloc((strlen(name) + 2) * sizeof(char));
	
	if (medicine->name == NULL)
		return NULL;
	
	strcpy(medicine->name, name);
	medicine->concentration = concentration;
	setPrice(medicine, price);
	setQuantity(medicine, quantity);
	return medicine;
}

void destroyMedicine(Medicine* medicine)
{
	/// <summary>
	/// Destruction of a medicine.
	/// </summary>
	/// <param name="medicine"> the medicine we want to destroy.</param>
	if (medicine == NULL)
		return;
	free(medicine->name);
	free(medicine);
	medicine = NULL;
}

//Below are implemented simple getters and setters 
char* getName(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;
	return medicine->name;
}

int getConcentration(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;
	return medicine->concentration;
}

int getQuantity(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;

	return medicine->quantity;
}

int getPrice(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;

	return medicine->price;
}

void setPrice(Medicine* medicine, int new_price) {
	medicine->price = new_price;
}

void setQuantity(Medicine* medicine, int quantity) {
	medicine->quantity = quantity;
}