#pragma once
#include "domain.h"

template<typename T>
class DynamicVector {
private:
	T* elements;
	int length{};
	int capacity{};
	void resize();

public:
	// DEFAULT CONSTRUCTOR IS THE NORMAL CONSTRUCTOR
	DynamicVector();
	// COPY CONSTRUCTOR
	DynamicVector(const DynamicVector& da);

	void add(T new_event);

	void remove(int position);

	void updateEvent(const T& new_element, int position);

	int size() const { return this->length; };

	T &operator[](int position){ return this->elements[position]; }

    DynamicVector<T> &operator=(const DynamicVector<T>& dynamicVectorCopy);

	int getCapacity() const { return this->capacity; };

	// there getters will get elements and a specific element.
	T* getElements() const { return this->elements; };

	~DynamicVector();
};

template<typename T>
DynamicVector<T>::DynamicVector() {
    this->length = 0;
    this->capacity = 2;
    this->elements = new T[2];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& da) {
    this->length = da.length;
    this->capacity = da.capacity;
    this->elements = new T[da.capacity];
    for(int i = 0; i < da.length; i++){
        T element{da.elements[i]};
        this->elements[i] = element;
    }
}
template<typename T>
void DynamicVector<T>::resize() {
    // the factor of resizing will always be 2
	T* copy_elements = new T[2 * this->capacity];
	for (int index = 0; index < this->length; index++) {
		// We will generate a new copy of the element
		T copy_element = this->elements[index];
		copy_elements[index] = copy_element;
	}
    this->capacity *= 2;
	delete[] this->elements;
	this->elements = copy_elements;
}

template<typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &dynamicVectorCopy) {
	T* copy_elements = new T[dynamicVectorCopy.capacity];
	for (int index = 0; index < dynamicVectorCopy.length; index++) {
		// We will generate a new copy of the element
		T copy_element = dynamicVectorCopy.elements[index];
		copy_elements[index] = copy_element;
	}
	this->length = dynamicVectorCopy.length;
	this->capacity = dynamicVectorCopy.capacity;
	delete[] this->elements;
	this->elements = copy_elements;

	return *this;
}

template<typename T>
void DynamicVector<T>::add(T new_event){
    	// if there are no empty spots in the array
	// then the dynamic array must be resized.
	if (this->length == this->capacity) {
		this->resize();
	}
	// the new element is added on the last position
	this->elements[this->length++] = new_event;
}

template<typename T>
void DynamicVector<T>::remove(int position){
//     if there are no empty spots in the array
//     then the dynamic array must be resized.
//    	// we will copy the element we want to delete, and then we delete it.
	T delete_element = this->elements[position];
	// we shift to the left with one position the elements starting from 'position'
	for (int index = position; index < this->length - 1; index++) {
		this->elements[index] = this->elements[index + 1];
	}
	this->length--;
}

template<typename T>
void DynamicVector<T>::updateEvent(const T& new_element, int position) {
    // we update the element on the given position and delete it
    T old_element = this->elements[position];
    this->elements[position] = new_element;
}
template<typename T>
DynamicVector<T>::~DynamicVector() {
    // When we call the destructor, besides deleting the memory allocated for the array,
    // we also need to delete the memory allocated for its elements
    delete[] this->elements;

}