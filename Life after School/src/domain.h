#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include"date.h"


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
		Event(std::string Title, std::string Description, Date date, int peopleNumber, std::string link);

		// copy constructor
		Event(const Event& e);

		// destructor
		~Event();

		std::string getTitle() const { return this->Title; };

		std::string getDescription() const{ return this->Description; };

		Date getDate() const { return this->date; };

		Event& operator=(const Event& event);

		int getPeopleNr() const { return this->peopleNumber; };

		std::string getLink() const { return this->link; };

		void updatePeople(int new_value);

		void updateDate(Date new_date);

        friend std::ostream& operator<<(std::ostream& os, const Event& e);
};

class Validation{
public:
    static bool checkIfNumber(const std::string& s);
};