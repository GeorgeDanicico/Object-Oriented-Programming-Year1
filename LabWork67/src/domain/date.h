#pragma once

#include<string>

using namespace std;
class Date {
	// This class will represent the schedule time for an event.
private:
	int year;
	int day;
	int month;
	int hour;
	int minutes;

public:
	Date();

	Date(int hour, int minutes, int day, int month, int year);
	~Date();

	Date &operator=(const Date &d);
    bool operator<(const Date &d) const;
    bool operator==(const Date &d) const;
	int getYear() const { return this->year; };
	int getDay() const { return this->day; };
	int getMonth() const { return this->month; };
	int getMinutes() const { return this->minutes; };
	int getHour() const { return this->hour; };

	string toString(){
	    string obj;
	    obj = to_string(hour) + "/" + to_string(minutes) + "/" + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	    return obj;
	}
	friend ostream& operator<<(ostream& os, const Date& date);

};