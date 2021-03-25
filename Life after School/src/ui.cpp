#include <iostream>
#include <cstring>
#include "ui.h"
#include<exception>

UI::~UI()=default;

void UI::entry_menu() {
    printf("\nExisting modes:\n");
    printf("\t-> admin mode -> enter admin.\n");
    printf("\t-> user mode -> enter user.\n");
    printf("\t-> exit -> exit.\n");
    printf("\n");
}

void UI::print_menu_admin() {
    std::cout<<"\nAdmin:\n";
    std::cout<<"\t-> add Event.\n";
    std::cout<<"\t-> delete Event.\n";
    std::cout<<"\t-> update Event.\n";
    std::cout<<"\t-> see all Event.\n";
    std::cout<<"\t-> exit.\n";
    std::cout<<"\n";
}

void UI::print_menu_user() {
    std::cout<<"\nUser:\n";
    std::cout<<"\t->create a new list of Events.\n";
    std::cout<<"\t->list available Events.\n";
    std::cout<<"\t->delete Event if you do not want to attend.\n";
    std::cout<<"\t->see all your events.\n";
    std::cout<<"\t->exit.\n";
}

void UI::start_application() {
    std::string entry_command;
    while(true){
        this->entry_menu();
        std::cout<<"Enter the command>";
        std::getline(std::cin, entry_command);
        if(entry_command == "admin" ){
            this->admin_UI();
            break;
        }
        else if (entry_command == "user"){
            this->user_UI();
            break;
        } else if (entry_command == "exit"){
            std::cout<<"Exiting...\n";
            break;
        }
        else std::cout<<"Invalid input entered.\n";

    }
}

void UI::admin_UI() {
    std::cout<<"Succesfully logged in with admin mode!\n";
    std::string admin_command;
    while(true){
        try {
            this->print_menu_admin();
            std::cout << "Enter the command>";
            std::getline(std::cin, admin_command);
            if (admin_command == "add")
                this->addUI();
            else if (admin_command == "delete")
                this->deleteUI("admin");
            else if (admin_command == "update")
                this->updateUI();
            else if (admin_command == "see")
                this->seeUI("admin");
            else if (admin_command == "exit") {
                this->user_service.clear(this->admin_service);
                break;
            }
            else
                std::cout << "Invalid command.\n";
        }
        catch(std::exception& e){
            std::cout << "An error occured." << "\n";
        }
    }
}

void UI::user_UI() {
    std::cout<<"Succesfully logged in with admin mode!\n";

    std::string user_command;
    while(true){
        try {
            this->print_menu_user();
            std::cout << "Enter the command>";
            std::getline(std::cin, user_command);
            if (user_command == "exit") {
                break;
            }else if (user_command == "create") {
                this->createUI(); }
            else if (user_command == "list") {
                this->listUI();
            } else if (user_command == "delete") {
                this->deleteUI("user");
            } else if (user_command == "show my list") {
                this->seeUI("user");
            } else std::cout << "Invalid command\n";
        }
        catch(std::exception& e){
            std::cout << "An error occured." << "\n";
        }
    }
}

std::string UI::readLine(std::string type) {
    std::string enter = "Enter the " + type;
    std::string command;
    std::cout << enter;
    std::getline(std::cin, command);
    return command;
}

void UI::addUI() {
    std::string hour, minutes, day, month, year, title, description, link, ppl;
    int people;
    title = this->readLine("title>");
    description = this->readLine("description>");
    link = this->readLine("link>");
    ppl = this->readLine("number of people>");
    hour = this->readLine("hour>");
    minutes = this->readLine("minutes>");
    day = this->readLine("day>");
    month = this->readLine("month>");
    year = this->readLine("year>");
    if (Validation::checkIfNumber(ppl))
        people = std::stoi(ppl);
    else{
        throw std::exception();
    }

    Date::validDate(hour, minutes, day, month, year);
    Date date2{std::stoi(hour), std::stoi(minutes), std::stoi(day), std::stoi(month), std::stoi(year)};
    if(this->admin_service.addServiceElement(title, description, date2, people, link)){
        std::cout<<"Event added succesfully!\n";
    }else{
        std::cout<<"Something wrong has occured.\n";
    }

}
void UI::deleteUI(std::string mode) {
    std::string title;
    title = this->readLine("title>");

    Service service_pointer = (mode == "admin" ? this->admin_service : this->user_service);

    if(!service_pointer.deleteServiceElement(title)){
        throw std::exception();
    }
    else{
        if(mode == "user"){
            this->admin_service.incdecPeople(title, -1);
        }
        std::cout<<"Deleted successfully!\n";
    }
}
void UI::updateUI() {
    std::string title, field, ppl, hour, minutes, day, month, year;
    int people = 0;
    Date date;

    title = this->readLine("title>");
    field = this->readLine("field>");
    if(field == "people"){
        ppl = this->readLine("new number of people>");
        if (Validation::checkIfNumber(ppl))
            people = std::stoi(ppl);
        else{
            throw std::exception();
        }
    }
    else if(field == "date"){
        hour = this->readLine("new hour>");
        minutes = this->readLine("new minutes>");
        day = this->readLine("new day>");
        month = this->readLine("new month>");
        year = this->readLine("new year>");
        Date::validDate(hour, minutes, day, month, year);
        Date date2{std::stoi(hour), std::stoi(minutes), std::stoi(day), std::stoi(month), std::stoi(year)};
        date = date2;
    }
    else throw std::exception();
    if(!this->admin_service.updateServiceElement(title, field, date, people))
        throw std::exception();
    else std::cout<<"Updated successfully!\n";

}
void UI::seeUI(std::string mode) {
    // In order to simplify, service_pointer will keep the address of either the user service
    // or the admin service, depending on the value of the variable mode.
    Service service_pointer = (mode == "user" ? this->user_service : this->admin_service);

//    if(mode == "user") service_pointer = this->user_service;
//    else service_pointer = this->admin_service;

    TElem *copied_elements = service_pointer.seeAllEvents();

    if(service_pointer.getRepo().getRepoSize() == 0){
        std::cout << "There are no events registered.\n";
        return;
    }

    for (int index = 0; index < service_pointer.getRepo().getRepoSize(); index++) {
        std::cout << index + 1 <<". "<< copied_elements[index];
    }
}

void UI::createUI() {
    this->user_service.clear(this->admin_service);
    std::cout << "You can create a new list.\n";
}

void UI::listUI() {
    std::string month;
    std::cout << "Enter month>";
    std::getline(std::cin, month);

    TElem* copied_elements;
    int events_length = 0;
    // If the month is empty we list all the events.
    if(month.empty()) {
        events_length = this->admin_service.getRepo().getRepoSize();
        copied_elements = this->admin_service.sortChronologically(this->admin_service.seeAllEvents(), events_length);
    }
    else{
        // If not, we apply a filtering.
        copied_elements = this->admin_service.filterEvents(month, events_length);
        copied_elements = this->admin_service.sortChronologically(copied_elements, events_length);
    }
    if(events_length == 0){
        std::cout << "Unfortunately there are no upcoming events.\n";
        return;
    }
    std::string my_response;
    while(true) {
        int exit_code = 0;
        for (int index = 0; index < events_length; index++) {
            std::cout << copied_elements[index];
            copied_elements[index].getTitle();
            std::string command = "start " + copied_elements[index].getLink();
            std::system(command.c_str());
            std::cout << "Do you want to take part in this event? yes / no / exit. \n";
            std::cout << "Your choice>";
            std::getline(std::cin, my_response);

            if (my_response == "exit") {
                exit_code = 1;
                break;
            } else if (my_response == "yes") {
                // After adding the event, we need to update the number of people that are going to that event
                if (this->user_service.addServiceElement(copied_elements[index].getTitle(),
                                                         copied_elements[index].getDescription(),
                                                         copied_elements[index].getDate(),
                                                         copied_elements[index].getPeopleNr() + 1,
                                                         copied_elements[index].getLink())) {
                    this->admin_service.incdecPeople(copied_elements[index].getTitle(), 1);
                    std::cout << "Event saved succesfully.\n";
                } else std::cout << "The event is already in your list.\n";

            }
            if (index < events_length - 1)
                std::cout << "Next...\n";
            if(index == events_length - 1){
                std::cout << "Do you want to go again through the events? yes/no.\n";
                std::getline(std::cin, command);
                if(command == "yes")
                    std::cout << "Restart list...\n";
                else{
                    exit_code = 1;
                    break;
                }
            }
        }
        if(exit_code == 1)
            break;
    }
    // if the events-length
    if(events_length != this->admin_service.getRepo().getRepoSize()){
        delete[] copied_elements;
    }
}
