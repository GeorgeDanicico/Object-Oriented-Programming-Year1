#include <iostream>
#include <map>

#include "ui.h"
UI::~UI()=default;

void UI::entry_menu() {
    printf("\nExisting modes:\n");
    printf("\t-> admin mode -> enter admin.\n");
    printf("\t-> user mode -> enter user.\n");
    printf("\t-> exit -> exit.\n");
    printf("\n");
}

void UI::print_menu_admin() {
    cout<<"\nAdmin:\n";
    cout<<"\t-> add Event.\n";
    cout<<"\t-> delete Event.\n";
    cout<<"\t-> update Event.\n";
    cout<<"\t-> see all Events.\n";
    cout<<"\t-> exit.\n";
    cout<<"\n";
}

void UI::print_menu_user() {
    cout<<"\nUser:\n";
    cout<<"\t->create a new list of Events.\n";
    cout<<"\t->list available Events.\n";
    cout<<"\t->delete Event if you do not want to attend.\n";
    cout<<"\t->show my list to see your events.\n";
    cout<<"\t->show the corresponding file.\n";
    cout<<"\t->exit.\n";
}

void UI::start_application() {
    string entry_command;

    map<string, function> commands;
    commands.insert(pair<string, function>("admin", &UI::admin_UI));
    commands.insert(pair<string, function>("user", &UI::user_UI));
    while(true){
        bool found = false;
        this->entry_menu();
        cout<<"Enter the command>";
        getline(cin, entry_command);
        if (entry_command == "exit"){
                cout<<"Exiting...\n";
                break;
        }
        else {
            for (auto &command : commands) {
                if (command.first == entry_command) {
                    (this->*command.second)();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid input entered.\n";
        }

    }
}

void UI::admin_UI() {
    cout<<"Successfully logged in with admin mode!\n";
    string admin_command;

    map<string, paramfunction> commands;
    commands.insert(pair<string, paramfunction>("add", &UI::addUI));
    commands.insert(pair<string, paramfunction>("delete", &UI::deleteUI));
    commands.insert(pair<string, paramfunction>("update", &UI::updateUI));
    commands.insert(pair<string, paramfunction>("see", &UI::seeUI));

    while(true){
        bool found = false;
        try {
            this->print_menu_admin();
            cout << "Enter the command>";
            getline(cin, admin_command);
            if(admin_command == "exit"){
                cout << "Exiting admin mode...\n";
                break;
            }
            else{
                for(auto& com : commands){
                    if(com.first == admin_command) {
                        (this->*com.second)("admin");
                        found = true;
                        break;
                    }
                }
                if(!found) cout << "Invalid command entered.\n";
            }
        }
        catch(ImplementedException& e){
            cout << e.what();
        }
    }
}

void UI::user_UI() {
    cout<<"Successfully logged in with admin mode!\n";

    map<string, paramfunction> commands;
    commands.insert(pair<string, paramfunction>("create", &UI::createUI));
    commands.insert(pair<string, paramfunction>("delete", &UI::deleteUI));
    commands.insert(pair<string, paramfunction>("list", &UI::listUI));
    commands.insert(pair<string, paramfunction>("show my list", &UI::seeUI));
    commands.insert(pair<string, paramfunction>("show", &UI::showfile));

    string user_command;
    while(true){
        try {
            bool found = false;
            this->print_menu_user();
            cout << "Enter the command>";
            getline(cin, user_command);
            if (user_command == "exit") {
                cout << "Exiting user mode...\n";
                break;
            }else{
                for(auto& com : commands){
                    if(com.first == user_command) {
                        (this->*com.second)("user");
                        found = true;
                        break;
                    }
                }
                if(!found) cout << "Invalid command entered.\n";
            }
        }
        catch(ImplementedException& e){
            cout << e.what();
        }
    }
}

std::string UI::readLine(const std::string& type) {
    string enter = "Enter the " + type;
    string command;
    cout << enter;
    getline(cin, command);
    return command;
}

void UI::addUI(const std::string& mode) {
    TElem elem;
    cin >> elem;

    if(this->service.addService(elem.getTitle(), elem.getDescription(), elem.getDate(), elem.getPeopleNr(),
                                elem.getLink(), "admin")){
        cout<<"Event added successfully!\n";
    }else{
        cout<<"Something wrong has occurred.\n";
    }

}
void UI::deleteUI(const std::string& mode) {
    string title;
    title = this->readLine("title>");

    if(!this->service.deleteService(title, mode)){
        throw ImplementedException("The event does not exist.\n");

    }
    else{
        if(mode == "user"){
            this->service.incdecPeople(title, -1, "admin");
        }
        cout<<"Deleted successfully!\n";
    }
}
void UI::updateUI(const std::string& mode) {
    string title, field, ppl, hour, minutes, day, month, year;
    int people = 0;
    Date date;

    title = this->readLine("title>");
    field = this->readLine("field>");
    if(field == "people"){
        ppl = this->readLine("new number of people>");
        if (Validation::checkIfNumber(ppl))
            people = stoi(ppl);
        else{
            throw ImplementedException("The number is invalid.\n");
        }
    }
    else if(field == "date"){
        hour = this->readLine("new hour>");
        minutes = this->readLine("new minutes>");
        day = this->readLine("new day>");
        month = this->readLine("new month>");
        year = this->readLine("new year>");
        Validation::validDate(hour, minutes, day, month, year);
        Date date2{stoi(hour), stoi(minutes), stoi(day), stoi(month), stoi(year)};
        date = date2;
    }
    else throw ImplementedException("Error: Invalid field entered.\n");
    if(!this->service.updateService(title, field, date, people, "admin"))
        throw ImplementedException("Error: Update unsuccessfully.\n");
    else cout<<"Updated successfully!\n";

}
void UI::seeUI(const std::string& mode) {
    // In order to simplify, service_pointer will keep the address of either the user service
    // or the admin service, depending on the value of the variable mode.
//    if(mode == "user") service_pointer = this->service;
//    else service_pointer = this->service;

    auto &elements = this->service.seeAllEvents(mode);

    if(elements.size() == 0){
        throw ImplementedException("Error: There are no events registered.\n");
    }
    int index =1;
    for(auto &elem : elements){
        cout << index << ". " << elem;
        index ++;
    }
    cout << endl;
}

void UI::createUI(const string& mode) {
    // this function can be user only by the user service!
    this->service.clear(this->service, mode);
    std::cout << "You can create a new list.\n";
}

void UI::listUI(const string& mode) {
//     This function is also used only by the user
    string month;
    cout << "Enter month>";
    getline(std::cin, month);

    vector<TElem> copied_elements(this->service.getRepo("admin").size());

//    // If the month is empty we list all the events.
    if(month.empty()) {
        copied_elements = this->service.seeAllEvents("admin");
        copied_elements = Service::sortChronologically(copied_elements);
    }
    else{
        // If not, we apply a filtering.
        copied_elements = this->service.filterEvents(copied_elements, month, "admin");
        copied_elements = Service::sortChronologically(copied_elements);
    }
    if(copied_elements.empty()){
        throw ImplementedException("Unfortunately there are no upcoming events.\n");
    }
    string my_response;
    while(true) {
        int exit_code = 0;
        int index = -1;
        for (auto &element : copied_elements) {
            cout << element;
            index ++;
            string command = "start " + element.getLink();
            system(command.c_str());
            cout << "Do you want to take part in this event? yes / no / exit. \n";
            cout << "Your choice>";
            getline(cin, my_response);

            if (my_response == "exit") {
                exit_code = 1;
                break;
            } else if (my_response == "yes") {
                // After adding the event, we need to update the number of people that are going to that event
                if (this->service.addService(element.getTitle(),
                                             element.getDescription(),
                                             element.getDate(),
                                             element.getPeopleNr(),
                                             element.getLink(), "user")) {

                    this->service.incdecPeople(element.getTitle(), 1, "admin");
                    this->service.incdecPeople(element.getTitle(), 1, "user");
                    cout << "Event saved successfully.\n";
                }
                else
                    cout << "The event is already in your list.\n";

            }
            if (index < copied_elements.size() - 1)
                cout << "Next...\n";
            if(index == copied_elements.size() - 1){
                cout << "Do you want to go again through the events? yes/no.\n";
                getline(cin, command);
                if(command == "yes")
                    cout << "Restart list...\n";
                else{
                    exit_code = 1;
                    break;
                }
            }
        }
        if(exit_code == 1)
            break;
    }
}

void UI::showfile(const string& mode) {
    cout << "Listing...\n\n";
    this->service.open();
}
