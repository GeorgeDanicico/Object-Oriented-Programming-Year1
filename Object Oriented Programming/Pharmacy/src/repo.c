
#include "repo.h"
#include<stdio.h>
#include<stdlib.h>

Repo* createRepo() {
	/// <summary>
	/// This function creates a repo.
	/// </summary>
	/// <returns>object of type Repo*</returns>
	Repo* repo = (Repo*)malloc(sizeof(Repo));
	if (repo == NULL)
		return NULL;

	repo->da = createDA(4);
	return repo;
}

void destroyRepo(Repo* repo){
	/// <summary>
	/// Destruction of the repo
	/// </summary>
	/// <param name="repo">the repo we want to destroy.</param>
	destroyDA(repo->da);
	free(repo);
}

int addRepo(Repo* repo, TElem element) {
	/// <summary>
	/// Addition of an element to the repo
	/// </summary>
	/// <param name="repo">The repo where we want to add an element.</param>
	/// <param name="element"> the element we want to add</param>
	/// <returns></returns>
	addElement(repo->da, element);
	return 1;
}

int deleteFromRepo(Repo* repo, int position) {
	/// <summary>
	/// Deletion of an element from the repo.
	/// </summary>
	/// <param name="repo">the repo</param>
	/// <param name="position">the position of the element we want to delete.</param>
	/// <returns></returns>
	if (position >= getRepoSize(repo))
		return -1;
	deleteElement(repo->da, position);
	return 1;
}

void updateRepo(Repo* repo, TElem element, int position, int field, int value) {
	/// <summary>
	/// Update of a specific element.
	/// </summary>
	/// <param name="repo">the repo.</param>
	/// <param name="element">The element we want to update.</param>
	/// <param name="position">the position of the element we want to update.</param>
	/// <param name="field">the field we want to update (1 for quantity/ 2 for price)</param>
	/// <param name="value">the new value of the specific field</param>
	if (field == 1)
		setQuantity(element, value);
	else
		setPrice(element, value);

	updateElement(repo->da, element, position);
	return 1;
}
// Below these are getters.
DynamicArray* getRepoElements(Repo* repo) {

	DynamicArray* new_array = createDA(getArraySize(repo->da));

	int index = 0;
	for (index = 0; index < getArraySize(repo->da); index++) {
		addElement(new_array, getElem(repo->da, index));
	}

	return new_array;
}

int getRepoSize(Repo* repo)
{
	return getArraySize(repo->da);
}