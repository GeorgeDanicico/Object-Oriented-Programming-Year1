#include "undo.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

Service* createService(Repo* repo)
{
	/// <summary>
	/// Creation of the service.
	/// </summary>
	/// <param name="repo">the repo</param>
	/// <returns>object of type Service*</returns>
	Service* service = (Service*)malloc(sizeof(Service));

	service->repo = repo;
	return service;
}

int addServiceElem(Service* service, char* name, int concentration, int quantity, int price) {
	/// <summary>
	/// Addition of an element to the service. We  create a new element with the parameters values.
	/// </summary>
	/// <param name="service">the service.</param>
	/// <param name="name">the name of the medicine</param>
	/// <param name="concentration">the concentration of the medicine</param>
	/// <param name="quantity">the quantity of the medicine</param>
	/// <param name="price">the price of the medicine</param>
	/// <returns></returns>
	TElem element = createMedicine(name, concentration, quantity, price);
	int succesfull = addRepo(service->repo, element);
	return succesfull;
}

int deleteServiceElem(Service* service, char* name, int concentration) {
	/// <summary>
	/// Deletion of an element by the unique identifiers.
	/// </summary>
	/// <param name="service">The service from which we will delete.</param>
	/// <param name="name">The name of the medicine</param>
	/// <param name="concentration">the concentration of the medicine</param>
	/// <returns></returns>
	int position = searchIdentifiers(service->repo->da, name, concentration);
	if (position == -1)
		return -1;

	return deleteFromRepo(service->repo, position);
}

int updateServiceElem(Service* service, char* name, int concentration, int field, int value) {
	/// <summary>
	/// Update of a specific element.
	/// </summary>
	/// <param name="service">the service where the element is located.</param>
	/// <param name="name">The name of the medicine we want to update.</param>
	/// <param name="concentration">The concentration of the medicine.</param>
	/// <param name="field">the filed we want to update</param>
	/// <param name="value">the new value </param>
	/// <returns></returns>
	int position = searchIdentifiers(service->repo->da, name, concentration);

	if (position == -1)
		return -1;

	if (value <= 0)
		return -1;

	TElem current_element = service->repo->da->medicines[position];
	TElem new_element = createMedicine(name, concentration, current_element->quantity, current_element->price);

	updateRepo(service->repo, new_element, position, field, value);

	return 1;
}

DynamicArray* listAllMedicinesFilter(Service* service, char* filter_string) {
	/// <summary>
	/// This function return a DA with the elements that have the filter_string in their name.
	/// </summary>
	/// <param name="service">the service</param>
	/// <param name="filter_string">the filter string</param>
	/// <returns>a DA with the elements mentioned above.</returns>
	int index = 0;
	// If the filter string is an empty string it means that we get all the lements
	if (!strcmp(filter_string, "")) {
		//for (index = 0; index < getRepoSize(service->repo); index++)
		//{
		//	list_array->medicines[index] = service->repo->da->medicines[index];
		//	list_array->current_length++;
		//}
		DynamicArray* list_array2 = getRepoElements(service->repo);
		return list_array2;
	}
	else{
		DynamicArray* list_array = createDA(getRepoSize(service->repo) + 2);
		for (index = 0; index < getRepoSize(service->repo); index++)
		{
			if (strstr(service->repo->da->medicines[index]->name, filter_string)) {
				
				list_array->medicines[list_array->current_length] = service->repo->da->medicines[index];
				list_array->current_length++;
			}
		}
		return list_array;

	}
	
}

DynamicArray* sortByName(DynamicArray* da, Relation r) {
	/// <summary>
	/// This function sorts the DA in ascending order by the Name of the medicines
	/// </summary>
	/// <param name="da">the dynamic array</param>
	/// <param name="r"> the relation that the elements will be sorted by.</param/
	/// <returns>the dynamic array sorted.</returns>
	int index1, index2;
	for (index1 = 0; index1 < da->current_length - 1; index1++)
	{
		for (index2 = index1 + 1; index2 < da->current_length; index2++){
			if (r(da->medicines[index1]->name, da->medicines[index2]->name) == 1) {
				TElem element = da->medicines[index1];
				da->medicines[index1] = da->medicines[index2];
				da->medicines[index2] = element;
			}
		}
	}
	return da;
}

DynamicArray* sortByConcetration(DynamicArray* da) {
	/// <summary>
	/// This function will sort the elements in the dynamic array by concentration. 
	/// </summary>
	/// <param name="da">the dynamic array we want to sort by concentrations.</param>
	/// <returns>a sorted dynamic array.</returns>
	int index1, index2;
	for (index1 = 0; index1 < da->current_length - 1; index1++)
	{
		for (index2 = index1 + 1; index2 < da->current_length; index2++) {
			if (getConcentration(getElem(da, index1)) < getConcentration(getElem(da, index2))) {
				TElem element = da->medicines[index1];
				da->medicines[index1] = da->medicines[index2];
				da->medicines[index2] = element;
			}
		}
	}
	return da;
}

DynamicArray* filterMedicines(Service* service, int field, int value) {
	/// <summary>
	/// Filter the medicine by a given number
	/// </summary>
	/// <param name="service">The service</param>
	/// <param name="value">the value</param>
	/// <returns></returns>
	DynamicArray* list_array = createDA(getRepoSize(service->repo) + 2);
	int index = 0;
	for (index = 0; index < getRepoSize(service->repo); index++) {
		TElem element = getElem(service->repo->da, index);
		if (field == 1) {
			if (getQuantity(element) < value) {
				list_array->medicines[list_array->current_length] = element;
				list_array->current_length++;
			}
		}
		else if (field == 2) {
			if (getPrice(element) < value) {
				list_array->medicines[list_array->current_length] = element;
				list_array->current_length++;
			}
		}
	}
	return list_array;
}

void destroyService(Service* service) {
	destroyRepo(service->repo);
	free(service);
}