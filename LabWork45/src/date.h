#pragma once

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
    bool operator<(const Date &d);
	static void validDate(const std::string& hour, const std::string& minutes, const std::string& day, const std::string& month, const std::string& year);
	int getYear() const { return this->year; };
	int getDay() const { return this->day; };
	int getMonth() const { return this->month; };
	int getMinutes() const { return this->minutes; };
	int getHour() const { return this->hour; };

};