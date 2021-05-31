#pragma once
#include "../domain/domain.h"
#include <vector>
#include <algorithm>
#include "../Exception.h"
#include <iostream>
#include <fstream>
typedef Event TElem;

using namespace std;


template<typename T>
class IRepo {
protected:
    vector<T>& STLVector; // this is the dynamic array.

public:

	// constructor
	IRepo(vector<T>& STLVector);
	// copy constructor

    IRepo(const IRepo &repo);

	virtual ~IRepo();

	virtual void add(const T& new_element)=0;
	virtual void remove(const T& element)=0;
	virtual void update(const T& new_element, int position)=0;
	virtual bool search(const T& element)=0;
    virtual vector<T>& get_all()=0;
    virtual const TElem& get_element(int position)=0;
    int size() const;
};

template<typename T>
IRepo<T>::IRepo(vector<T>& STLVector):STLVector(STLVector) {}

template <typename T>
IRepo<T>::IRepo(const IRepo &repo):STLVector(repo.STLVector)  {
    this->file_name = repo.file_name;
}

template<typename T>
int IRepo<T>::size() const {
    return this->STLVector.size();
}

template <typename T>
IRepo<T>::~IRepo()= default;
