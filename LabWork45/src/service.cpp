#include <iostream>
#include <exception>
#include "service.h"

//Constructor

Service::Service(const Service &service):admin_repo(service.admin_repo), user_repo(service.user_repo){}

Service::~Service() = default;

bool Service::addServiceElement(std::string Title, std::string Description, Date date, int people, std::string link, const std::string &mode) {
    // we add a new element
    // We check if one of the fields is empty ( date and people doesnt require validation. )

    if(Title.empty() || Description.empty() || link.empty())
        throw std::exception();

    Repository repo = this->getRepo(mode);

    // we parse through all the elements of the repository to check if there is one with the same title
    TElem* copied_elem = repo.getRepoElements();
    for(int index = 0; index < repo.getRepoSize(); index ++){
        if(copied_elem[index].getTitle() == Title) {
            return false;
        }
    }
    // if not, then we add the new event;

    TElem new_element{Title, Description, date, people, link};
    repo.addRepoElement(new_element);
    return true;
}

bool Service::deleteServiceElement(std::string title_identifier, const std::string& mode) {
    // We search for a specific title
    // In case we found the title, we delete it and return true
    // otherwise return false
    Repository repo = this->getRepo(mode);

    TElem* Elements = repo.getRepoElements();
    for(int index = 0; index < repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == title_identifier){
            repo.deleteRepoElement(index);

//             if we are in the admin mode, and we change a new element, we must make sure that
//             the event in the user list is also updated.
            if(mode == "admin"){
                TElem* user_list = this->user_repo.getRepoElements();
                for (int user_index = 0; user_index < this->user_repo.getRepoSize(); user_index++){
                    if(user_list[user_index].getTitle() == title_identifier){
                        this->user_repo.deleteRepoElement(user_index);
                        break;
                    }
                }
            }
            return true;
        }
    }
    return false;

}

bool Service::updateServiceElement(std::string title_identifier, std::string field, Date date, int people, const std::string& mode) {
    // This function will search for the element with the corresponding title
    // and in case it exists, it will create a new object, and replace it.
    Repository repo = this->getRepo(mode);

    TElem* Elements = repo.getRepoElements();
    for(int index = 0; index < repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == title_identifier){
            TElem new_elem = repo.getRepoElement(index);
            if(field == "date")
                new_elem.updateDate(date);
            else new_elem.updatePeople(people);

            repo.updateRepoElement(new_elem, index);
//             if we are in the admin mode, and we change a new element, we must make sure that
            // the event in the user list is also updated.
            if(mode == "admin"){
                TElem* user_list = this->user_repo.getRepoElements();
                for (int user_index = 0; user_index < this->user_repo.getRepoSize(); user_index++){
                    if(user_list[user_index].getTitle() == new_elem.getTitle()){
                        TElem copy{new_elem};
                        this->user_repo.updateRepoElement(copy, user_index);
                        break;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

void Service::clear(Service& service, const std::string& mode){
    // This function will clear the entire repo
    // It is best used for the user service.
    Repository repo = this->getRepo(mode);

    int length = repo.getRepoSize();
    while(length){
        std::string title = repo.getRepoElement(0).getTitle();
        repo.deleteRepoElement(0);
        service.incdecPeople(title, -1, "admin");
        length --;
    }
}

TElem* Service::filterEvents(std::string month, int &length, const std::string& mode) {
    // We will filter the events by a given month entered by the user
    // As validations, if the month isn't valid, we throw an exception.
    // If it is valid, we simply find the elements that satisfy our condition.
    if(!Validation::checkIfNumber(month) || std::stoi(month) > 12){
        throw std::exception();
    }

    Repository repo = this->getRepo(mode);

    int int_month = std::stoi(month);

    // we prepare the new array of elements.
    TElem* filtered_elements = new TElem[this->getRepo(mode).getRepoSize()];
    // The repo elements are copied in order to make the parsing easier.
    TElem* repo_elem = repo.getRepoElements();
    for(int index = 0; index < repo.getRepoSize(); index++ ){
        // if the element have the required month, we make a deep copy and append it to the
        // filtered vector.
        if(repo_elem[index].getDate().getMonth() == int_month){
            TElem new_elem{repo_elem[index]};
            filtered_elements[length++] = new_elem;
        }
    }
    return filtered_elements;
}

bool Service::incdecPeople(std::string Title,int factor, const std::string &mode) {
    // This function is used only for incrementing the number of people
    Repository repo = this->getRepo(mode);

    TElem* Elements = repo.getRepoElements();
    for(int index = 0; index < repo.getRepoSize(); index++ ){
        if(Elements[index].getTitle() == Title){
            TElem new_elem = repo.getRepoElement(index);
            new_elem.updatePeople(new_elem.getPeopleNr() + factor);
            repo.updateRepoElement(new_elem, index);
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
                std::swap(elements[i], elements[i+1]);
            }
        }
    }
    return elements;
}
// The below function is like a getter, it returns the reference to the desired repo.
Repository &Service::getRepo(const std::string &mode) {
    if(mode == "admin")
        return this->admin_repo;
    else return this->user_repo;
}

TElem *Service::seeAllEvents(const std::string &mode) {
    if(mode == "admin")
        return this->admin_repo.getRepoElements();
    else return this->user_repo.getRepoElements();
}