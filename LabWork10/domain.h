#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include"date.h"

using namespace std;

class Event {
	private:
		std::string Title;
		std::string Description;
		Date date;
		int peopleNumber;
		std::string link;

	public:
		//default constructor
		Event();
		// constructor
		Event(const string& Title, const string& Description, const Date& date, int peopleNumber, const string& link);

		// copy constructor
		Event(const Event& e);

		// destructor
		~Event();

		string getTitle() const { return this->Title; };

		string getDescription() const{ return this->Description; };

		Date getDate() const { return this->date; };

		Event& operator=(const Event& event);

		bool operator==(const Event& event) const;

		int getPeopleNr() const { return this->peopleNumber; };

		string getLink() const { return this->link; };

		void updatePeople(int new_value);

		void updateDate(const Date& new_date);

        friend ostream& operator<<(ostream& os, const Event& e);

        friend istream& operator>>(istream& is, Event &e);
};

class Validation{
public:
    static bool checkIfNumber(const std::string& s);
    static void validDate(const std::string& hour, const std::string& minutes, const std::string& day, const std::string& month, const std::string& year);

};