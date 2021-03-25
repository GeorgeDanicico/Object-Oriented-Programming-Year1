#include <iostream>
#include <exception>
#include "service.h"

//Constructor



Service::~Service() = default;

bool Service::addServiceElement(std::string Title, std::string Description, Date date, int people, std::string link) {
    // we add a new element
    // We check if one of the fields is empty ( date and people doesnt require validation. )

    if(Title.empty() || Description.empty() || link.empty())
        throw std::exception();

    // we parse through all the elements of the repository to check if there is one with the same title
    TElem* copied_elem = this->repo.getRepoElements();
    for(int index = 0; index < this->repo.getRepoSize(); index ++){
        if(copied_elem[index].getTitle() == Title) {
            return false;
        }
    }
    // if not, then we add the new event;

    TElem new_element{Title, Description, date, people, link};
    this->repo.addRepoElement(new_element);
    return true;
}

bool Service::deleteServiceElement(std::string title_identifier) {
    // We search for a specific title
    // In case we found the title, we delete it and return true
    // otherwise return false
    TElem* Elements = this->repo.getRepoElements();
    for(int index = 0; index < this->repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == title_identifier){
            this->repo.deleteRepoElement(index);
            return true;
        }
    }
    return false;

}

bool Service::updateServiceElement(std::string title_identifier, std::string field, Date date, int people) {
    // This function will search for the element with the corresponding title
    // and in case it exists, it will create a new object, and replace it.
    TElem* Elements = this->repo.getRepoElements();
    for(int index = 0; index < this->repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == title_identifier){
            TElem new_elem = this->repo.getRepoElement(index);
            if(field == "date")
                new_elem.updateDate(date);
            else new_elem.updatePeople(people);

            this->repo.updateRepoElement(new_elem, index);
            return true;
        }
    }
    return false;
}

void Service::clear(Service& service){
    // This function will clear the entire repo
    // It is best used for the user service.
    TElem* Elements = this->repo.getRepoElements();
    int length = this->repo.getRepoSize();
    while(length){
        std::string title = this->repo.getRepoElement(0).getTitle();
        this->repo.deleteRepoElement(0);
        service.incdecPeople(title, -1);
        length --;
    }
}

TElem* Service::filterEvents(std::string month, int &length) {
    // We will filter the events by a given month entered by the user
    // As validations, if the month isn't valid, we throw an exception.
    // If it is valid, we simply find the elements that satisfy our condition.
    if(!Validation::checkIfNumber(month) || std::stoi(month) > 12){
        throw std::exception();
    }
    int int_month = std::stoi(month);
    // we prepare the new array of elements.
    TElem* filtered_elements = new TElem[this->getRepo().getRepoSize()];
    // The repo elements are copied in order to make the parsing easier.
    TElem* repo_elem = this->repo.getRepoElements();
    for(int index = 0; index < this->repo.getRepoSize(); index++ ){
        // if the element have the required month, we make a deep copy and append it to the
        // filtered vector.
        if(repo_elem[index].getDate().getMonth() == int_month){
            TElem new_elem{repo_elem[index]};
            filtered_elements[length++] = new_elem;
        }
    }

    return filtered_elements;
}

bool Service::incdecPeople(std::string Title,int factor) {
    // This function is used only for incrementing the number of people
    TElem* Elements = this->repo.getRepoElements();
    for(int index = 0; index < this->repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == Title){
            TElem new_elem = this->repo.getRepoElement(index);
            new_elem.updatePeople(new_elem.getPeopleNr() + factor);
            this->repo.updateRepoElement(new_elem, index);
            return true;
        }
    }
    return false;
}

TElem *Service::sortChronologically(TElem *elements, const int& length) {
    // this function is going to sort the elements chronologically
    for(int i = 0; i < length - 1; i++){
        for(int j = i + 1; j < length; j++) {
            if (elements[i + 1].getDate() < elements[i].getDate()) {
                Date aux;
                aux = elements[i].getDate();
                elements[i].updateDate(elements[i + 1].getDate());
                elements[i + 1].updateDate(aux);
            }
        }
    }
    return elements;
}

