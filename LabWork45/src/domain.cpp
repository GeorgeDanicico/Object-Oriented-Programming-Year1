#include <iostream>
#include "domain.h"

Event::Event() {
	this->Title = "";
	this->Description = "";
	this->peopleNumber = 0;
	this->link = "";
	Date d;
	this->date = d;
}


Event::Event(std::string Title, std::string Description, Date date, int peopleNumber, std::string link) {
	this->Title = Title;
	this->Description = Description;
	this->date = date;
	this->link = link;
	this->peopleNumber = peopleNumber;

}
// The COPY CONSTRUCTOR.
Event::Event(const Event& e) {
	this->Title = e.Title;
	this->Description = e.Description;
	this->date = e.date;
	this->link = e.link;
	this->peopleNumber = e.peopleNumber;
}

Event::~Event() = default;

// Setters
void Event::updatePeople(int new_value) {
	this->peopleNumber = new_value;
}

void Event::updateDate(Date new_date) {
	this->date = new_date;
}

std::ostream &operator<<(std::ostream &os, const Event& e) {
    // This is the overload operator for printing.
    std::string date = std::to_string(e.getDate().getHour()) + "/" + std::to_string(e.getDate().getMinutes()) +"/";
    date = date + std::to_string(e.getDate().getDay()) + "/" + std::to_string(e.getDate().getMonth()) + "/";
    date = date + std::to_string(e.getDate().getYear());
    os <<"Title: "<< e.getTitle() << "; Description: "<<e.getDescription()<<"; Date: "<< date << "; People:" << e.getPeopleNr() << "; Link: " << e.getLink() << "\n";
    return os;
}

Event &Event::operator=(const Event &event) {
    this->Title = event.Title;
    this->peopleNumber = event.peopleNumber;
    this->link = event.link;
    this->Description = event.Description;
    this->date = event.date;

    return *this;
}

bool Validation::checkIfNumber(const std::string& s) {

    std::string::const_iterator it = s.begin();
    while(it != s.end() and std::isdigit(*it))  ++it;

    return it == s.end() && !s.empty();

}
