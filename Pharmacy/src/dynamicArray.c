#include"dynamicArray.h"
#include<stdio.h>


DynamicArray* createDA(int capacity) {
	/// <summary>
	/// Creation of a dynamic array with a specific capacity.
	/// </summary>
	/// <param name="capacity"> the capacity of the new dynamic array.</param>
	/// <returns></returns>
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	// check if space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->current_length = 0;
	da->medicines = (TElem*)malloc(capacity * sizeof(TElem));

	if (da->medicines == NULL)
		return NULL;

	return da;
}

void destroyDA(DynamicArray* da) {
	/// <summary>
	/// Destruction of a dynamic array.
	/// </summary>
	/// <param name="da"> the DA we want to destroy.</param>
	if (da == NULL)
		return;
	int index = 0;
	if (da->current_length == 0) {
		free(da->medicines);
	}
	else {
		// freeing all the space that was allocated.
		for (index = 0; index < da->current_length; index++) {
			destroyMedicine(da->medicines[index]);
		}
		free(da->medicines);
	}
	free(da);
	da = NULL;
}

void resizeDA(DynamicArray* da) {
	/// <summary>
	/// Resize of the array
	/// </summary>
	/// <param name="da">the DA we want to resize.</param>
	if (da == NULL)
		return;
	// allocating a new array of elements with the capacity doubled.
	TElem* new_array = (TElem*)malloc(2 * da->capacity * sizeof(TElem));
	if (new_array == NULL)
		return;
	
	da->capacity = 2 * da->capacity;

	int index = 0;
	// copy the array of elements
	for (index = 0; index < da->current_length; index++)
		new_array[index] = da->medicines[index];
	// freeing the previous array and initialize with the new one.
	free(da->medicines);
	da->medicines = new_array;
}

void addElement(DynamicArray* da, TElem element) {
	/// <summary>
	/// Adding of an element. If the element is already in the array, its quantity is updated.
	/// </summary>
	/// <param name="da">the DA where we will add an element</param>
	/// <param name="element">the element we want to add.</param>
	if (da == NULL)
		return;
	if (da->capacity == da->current_length)
		resizeDA(da);

	int position = searchIdentifiers(da, element->name, element->concentration);

	if (position != -1){
		// we just update the quantity by adding the new quantity
		// if the item is identified by the name and the concentration/ but the price is different, the old price will be kept.
		setQuantity(da->medicines[position], da->medicines[position]->quantity + element->quantity);
		destroyMedicine(element);
	}
	else {
		da->medicines[da->current_length] = element;
		da->current_length++;
	}
}

int searchIdentifiers(DynamicArray* da, char* identifier1, int identifier2)
{
	/// <summary>
	/// This function checks if there is a specific element in the array based on the unique identifiers.
	/// </summary>
	/// <param name="da">the DA in which we are looking for the identifiers.</param>
	/// <param name="identifier1">the name of the medicine</param>
	/// <param name="identifier2">the concentration of the medicine</param>
	/// <returns>the position of the element/ -1 if it is not in the array.</returns>
	int index = 0;
	for (index = 0; index < da->current_length; index++)
	{
		if (!strcmp(da->medicines[index]->name, identifier1) && da->medicines[index]->concentration == identifier2)
			return index;
	}
	return -1;
}

void deleteElement(DynamicArray* da, int position)
{
	/// <summary>
	/// Deletion of an element of the DA.
	/// </summary>
	/// <param name="da">the DA from which we will delete an element.</param>
	/// <param name="position">the position of the element we want to delete.</param>
	if (da == NULL || (position < 0 || position >= da->current_length))
		return;

	// if there are elements in the array we can delete them
	if (da->current_length > 0)
	{
		int index = 0;
		TElem copy_destroy_elem = da->medicines[position];
		for (index = position; index < da->current_length - 1; index++)
			da->medicines[index] = da->medicines[index + 1];
		
		destroyMedicine(copy_destroy_elem);
		da->current_length--;
	}
}

void updateElement(DynamicArray* da, TElem new_elem, int position) {
	/// <summary>
	/// The update of an element.
	/// </summary>
	/// <param name="da">the DA where we are going to perform the update.</param>
	/// <param name="new_elem">the new element we want in the array</param>
	/// <param name="position"> the position of the element we want to update</param>
	destroyMedicine(da->medicines[position]);
	da->medicines[position] = new_elem;
}
//Below there are 2 getters.
int getArraySize(DynamicArray* da) {
	return da->current_length;
}

TElem getElem(DynamicArray* da, int position) {
	return da->medicines[position];
}