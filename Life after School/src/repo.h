#pragma once
#include"dynamicArray.h"

typedef Event TElem;

class Repository {
private:
    DynamicVector<TElem>& dynamicVector; // this is the dynamic array.
	std::string file_name;

public:

	// constructor
	Repository(DynamicVector<TElem>& dV, const std::string& file_name);
	// copy constructor

    Repository(const Repository &repo);

	~Repository();

	TElem* getRepoElements() const { return this->dynamicVector.getElements(); };

	TElem& getRepoElement(int position) const { return this->dynamicVector[position]; }

	int getRepoSize() const { return this->dynamicVector.size(); };

	void  addRepoElement(const TElem& new_element);

	void deleteRepoElement(int position);

	void updateRepoElement(const TElem& new_element, int position);

	void loadFromFile();

	void saveToFile();

};