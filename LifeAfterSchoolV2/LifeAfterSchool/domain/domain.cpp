#include <iostream>
#include "domain.h"
#include "../Exception.h"

Event::Event() {
	this->Title = "";
	this->Description = "";
	this->peopleNumber = 0;
	this->link = "";
	Date d;
	this->date = d;
}


Event::Event(const string& Title, const string& Description, const Date& date, int peopleNumber, const string& link) {
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

void Event::updateDate(const Date& new_date) {
	this->date = new_date;
}

ostream &operator<<(ostream &os, const Event& e) {
    // This is the overload operator for printing.
    string date = to_string(e.getDate().getHour()) + "/" + to_string(e.getDate().getMinutes()) +"/";
    date = date + to_string(e.getDate().getDay()) + "/" + to_string(e.getDate().getMonth()) + "/";
    date = date + to_string(e.getDate().getYear());
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

istream& operator>>(istream &is, Event& e) {

    string hour, minutes, day, month, year, people;

    cout << "Enter the title: ";
    getline(is, e.Title);
    cout << "Enter the description: ";
    getline(is, e.Description);
    cout << "Enter the link: ";
    getline(is, e.link);
    cout << "Enter the people: ";
    getline(is, people);
    cout << "Enter the hour: ";
    getline(is, hour);
    cout << "Enter the minutes: ";
    getline(is, minutes);
    cout << "Enter the day: ";
    getline(is, day);
    cout << "Enter the month: ";
    getline(is, month);
    cout << "Enter the year: ";
    getline(is, year);
    if (Validation::checkIfNumber(people))
        e.peopleNumber = stoi(people);
    else{
        throw ImplementedException("Error: Invalid number of people.\n");
    }

    Validation::validDate(hour, minutes, day, month, year);
    Date date{stoi(hour), stoi(minutes), stoi(day), stoi(month), stoi(year)};
    e.date = date;

    return is;
}

bool Event::operator==(const Event &event) const{
    if(this->Title != event.Title)
        return false;
    if(this->Description != event.Description)
        return false;
    return true;
}

bool Validation::checkIfNumber(const std::string& s) {

    std::string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it))  it++;

    return it == s.end() && !s.empty();

}

void Validation::validDate(const std::string& hour, const std::string& minutes, const std::string& day, const std::string& month, const std::string& year) {
    // this function checks the values for a valid date.
    int hourint, minutesint, dayint, monthint, yearint;
    if (Validation::checkIfNumber(hour) && Validation::checkIfNumber(day) && Validation::checkIfNumber(minutes)
        && Validation::checkIfNumber(month) && Validation::checkIfNumber(year) ) {
        hourint = std::stoi(hour);
        minutesint = std::stoi(minutes);
        dayint = std::stoi(day);
        monthint = std::stoi(month);
        yearint = std::stoi(year);
    }
    else{
        throw ImplementedException("Error: Invalid date.\n");
    }


    if(dayint < 1 || dayint > 31 || monthint < 0 || monthint > 12 || yearint < 2020 ){
        throw ImplementedException("Error: Invalid date.\n");
    }
    if(hourint < 0 || hourint > 23 || minutesint < 0 || minutesint > 59)
    {
        throw ImplementedException("Error: Invalid date.\n");
    }

}
