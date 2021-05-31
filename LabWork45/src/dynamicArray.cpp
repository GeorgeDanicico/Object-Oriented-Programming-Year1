//#include<iostream>
//#include"dynamicArray.h"
//#include<exception>
//
//DynamicVector::DynamicVector() {
//	this->elements = new TElem[2];
//	this->length = 0; // the current number of events
//	this->capacity = 2; // the number of the events that can be held.
//}
//// the copy constructor
//DynamicVector::DynamicVector(const DynamicVector& dynamicVector) {
//	this->elements = new TElem[dynamicVector.capacity];
//	for (int index = 0; index < dynamicVector.length; index++) {
//        this->elements[index] = dynamicVector.elements[index];
//        //printf("%p %p\n",&this->elements[index], &dynamicVector.elements[index]);
//    }
//	this->capacity = dynamicVector.capacity;
//	this->length = dynamicVector.length;
//}
//
////This function will resize the array
//void DynamicVector::resize() {
//	TElem* copy_elements = new TElem[2 * this->capacity];
//	for (int index = 0; index < this->length; index++) {
//		// We will generate a new copy of the element
//		TElem copy_element = (this->elements[index]);
//		copy_elements[index] = copy_element;
//	}
//    this->capacity *= 2;
//	delete[] this->elements;
//	this->elements = copy_elements;
//}
//
//void DynamicVector::add(TElem new_event) {
//	// if there are no empty spots in the array
//	// then the dynamic array must be resized.
//	if (this->length == this->capacity) {
//		this->resize();
//	}
//	// the new element is added on the last position
//	this->elements[this->length++] = new_event;
//}
//
//void DynamicVector::remove(int position) {
//	// we will copy the element we want to delete, and then we delete it.
//	TElem delete_element = this->elements[position];
//	// we shift to the left with one position the elements starting from 'position'
//	for (int index = position; index < this->length - 1; index++) {
//		this->elements[index] = this->elements[index + 1];
//	}
//	this->length--;
//}
//
//void DynamicVector::updateEvent(const TElem& new_element, int position) {
//	// we update the element on the given position and delete it
//	TElem old_element = this->elements[position];
//	this->elements[position] = new_element;
//
//}
//
//DynamicVector::DynamicVectornamicVector() {
//	// When we call the destructor, besides deleting the memory allocated for the array,
//	// we also need to delete the memory allocated for its elements
//	delete[] this->elements;
//}
