#include <iostream>
#include "service.h"
#include "addoperation.h"
#include "deloperation.h"
#include "updateoperation.h"


//Constructor

Service::Service(const Service &service):admin_repo(service.admin_repo), user_repo(service.user_repo), storage(service.storage){}

Service::~Service() = default;

bool Service::addService(const std::string& Title, const std::string& Description, const Date& date, int people, const std::string& link, const std::string &mode) {
    // we add a new element
    // We check if one of the fields is empty ( date and people doesnt require validation. )

    if(Title.empty() || Description.empty() || link.empty())
        throw ImplementedException("Error: You are trying to enter an invalid element.\n");

    IRepo<TElem> &repo = this->getRepo(mode);

    // we parse through all the elements of the repository to check if there is one with the same title
    vector<TElem>& copied_elem = repo.get_all();
    TElem new_element{Title, Description, date, people, link};
    auto it = find(copied_elem.begin(), copied_elem.end(), new_element);
    // if not, then we add the new event;
    if(it == copied_elem.end()) {
        repo.add(new_element);
        storage->write();

        Operation* o = new addOp{&this->getRepo(mode), new_element};
        if(mode == "admin"){
            this->admin_undo.push_back(o);
            this->admin_redo.clear();
        }
        else{
            this->incdecPeople(new_element.getTitle(), 1, "admin");
            this->incdecPeople(new_element.getTitle(), 1, "user");
            this->user_undo.push_back(o);
            this->user_redo.clear();
        }

        return true;
    }
    else
        return false;
}

bool Service::deleteService(const string& title_identifier, const string& mode) {
    // We search for a specific title
    // In case we found the title, we delete it and return true
    // otherwise return false
    IRepo<TElem> &repo = this->getRepo(mode);

    vector<TElem>& Elements = repo.get_all();

    auto it = find_if(Elements.begin(), Elements.end(), [&title_identifier](const TElem& x){return x.getTitle() == title_identifier;});
    if(it != Elements.end()) {

        TElem new_element = *it;
        repo.remove(*it);

        Operation* o = new delOp{ &this->getRepo(mode), new_element };
        if (mode == "admin") {
            vector<TElem> &user_list = this->user_repo->get_all();
            auto it_user = find_if(user_list.begin(), user_list.end(), [&title_identifier](const TElem &x) { return x.getTitle() == title_identifier; });
            if (it_user != user_list.end()) {
                this->user_repo->remove(*it_user);

            }
            this->admin_undo.push_back(o);
            this->admin_redo.clear();
        }
        else {
            this->incdecPeople(new_element.getTitle(), -1, "admin");
            this->user_undo.push_back(o);
            this->user_redo.clear();
        }
        storage->write();
        return true;
    }

    return false;

}

bool Service::updateService(const std::string& title_identifier, const std::string& field, const Date& date, int people, const std::string& mode) {
    // This function will search for the element with the corresponding title
    // and in case it exists, it will create a new object, and replace it.
    IRepo<TElem> &repo = this->getRepo(mode);

    vector<TElem>& Elements = repo.get_all();

    auto it = find_if(Elements.begin(), Elements.end(), [&title_identifier](const TElem& x){return x.getTitle() == title_identifier;});
    if(it != Elements.end()) {
        TElem old_elem = repo.get_element(distance(Elements.begin(), it));

        int dist = distance(Elements.begin(), it);
        TElem new_elem = old_elem;
        if(field == "date")
            new_elem.updateDate(date);
        else new_elem.updatePeople(people);
        
        Operation* o = new updateOp(&this->getRepo(mode), new_elem, old_elem, dist);

        if (mode == "admin") {
            this->admin_undo.push_back(o);
            this->admin_redo.clear();
        }

        repo.update(new_elem, dist);

        if(mode == "admin") {
            vector<TElem> &user_list = this->user_repo->get_all();
            auto it_user = find_if(user_list.begin(), user_list.end(),[&title_identifier](const TElem &x) { return x.getTitle() == title_identifier; });
            if (it_user != user_list.end()) {
                this->user_repo->update(new_elem, distance(user_list.begin(), it_user));
            }
        }
        storage->write();
        return true;
    }
    return false;
}

void Service::clear(Service& service, const std::string& mode){
    // This function will clear the entire repo
    // It is used for the user service when the user wants to create a new list.
    IRepo<TElem> &repo = this->getRepo(mode);

    int length = repo.size();
    while(length){
        string title = repo.get_element(0).getTitle();
        auto it = repo.get_all().begin();
        repo.remove(*it);
        service.incdecPeople(title, -1, "admin");
        length --;
    }
    if(mode == "user")
        storage->write();
}

vector<TElem>& Service::filterEvents(vector<TElem>& filtered_vector, const std::string& month, const std::string& mode) {
    // We will filter the events by a given month entered by the user
    // As validations, if the month isn't valid, we throw an exception.
    // If it is valid, we simply find the elements that satisfy our condition.
    if(!Validation::checkIfNumber(month) || std::stoi(month) > 12){
        throw ImplementedException("Error: Invalid month.\n");
    }

    IRepo<TElem>& repo = this->getRepo(mode);

    int int_month = stoi(month);

    // we prepare the new array of elements.
    // The repo elements are copied in order to make the parsing easier.
    vector<TElem> repo_elem = repo.get_all();
    auto it = copy_if(repo_elem.begin(), repo_elem.end(), filtered_vector.begin(), [int_month](const TElem& elem){return elem.getDate().getMonth() == int_month;});
    filtered_vector.resize(distance(filtered_vector.begin(), it));
    return filtered_vector;
}

bool Service::incdecPeople(const std::string& Title,int factor, const std::string &mode) {
    // This function is used only for incrementing the number of people
    IRepo<TElem> &repo = this->getRepo(mode);

    vector<TElem>& Elements = repo.get_all();

    int position = 0;
    for(auto &element : Elements){
        if(element.getTitle() == Title){
            TElem new_elem = repo.get_element(position);
            new_elem.updatePeople(new_elem.getPeopleNr() + factor);
            repo.update(new_elem, position);
            return true;
        }
        position ++;
    }
    return false;
}

bool compareDates(const TElem& e1, const TElem& e2){
    return e1.getDate() < e2.getDate();
}

vector<TElem>& Service::sortChronologically(vector<TElem>& elements) {
    // this function is going to sort the elements chronologically

    sort(elements.begin(), elements.end(), compareDates);

    return elements;
}
// The below function is like a getter, it returns the reference to the desired repo.
IRepo<TElem> &Service::getRepo(const std::string &mode) {
    if(mode == "admin")
        return *this->admin_repo;
    else return *this->user_repo;
}

vector<TElem>& Service::seeAllEvents(const std::string &mode) {
    if(mode == "admin")
        return this->admin_repo->get_all();
    else return this->user_repo->get_all();
}

void Service::open() {
    this->storage->write();
    this->storage->open();
}

vector<int> Service::monthEvents() {

    vector<int> monthsEventsCounter;
    monthsEventsCounter.reserve(12);
for(int i=0; i<12; i++){
        monthsEventsCounter.push_back(0);
    }

    vector<Event> events = this->getRepo("admin").get_all();
    for(auto &ev : events){
        int month = ev.getDate().getMonth();
        monthsEventsCounter[month-1] ++;
    }
    return monthsEventsCounter;
}


bool Service::Undo(string& mode) {
    if(mode == "admin"){
        if(this->admin_undo.empty())
            return false;
        Operation* o = this->admin_undo.back();
        o->undo();
        this->admin_undo.pop_back();
        this->admin_redo.push_back(o);
        return true;
    }
    else{
        if(this->user_undo.empty())
            return false;
    
        Operation* o = this->user_undo.back();
        o->undo();
        this->user_undo.pop_back();
        this->user_redo.push_back(o);
        return true;
    }
    return false;
}

bool Service::Redo(string& mode) {
    if(mode == "admin"){
        if(this->admin_redo.empty())
            return false;
        Operation* o = this->admin_redo.back();
        o->redo();
        this->admin_redo.pop_back();
        this->admin_undo.push_back(o);
        return true;
    }
    else{
        if(this->user_redo.empty())
            return false;
    
        Operation* o = this->user_redo.back();
        o->redo();
        this->user_redo.pop_back();
        this->user_undo.push_back(o);
        return true;
    }

}
