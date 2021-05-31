#include<iostream>
#include "date.h"
#include "domain.h"

Date::Date() {
	this->hour = 0;
	this->minutes = 0;
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

Date::Date(int hour, int minutes, int day, int month, int year) {
	this->hour = hour;
	this->minutes = minutes;
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::~Date() = default;

// we overload the operate = in order to swap dates easily
Date &Date::operator=(const Date &d) {
	this->hour = d.hour;
	this->minutes = d.minutes;
	this->day = d.day;
	this->month = d.month;
	this->year = d.year;

	return *this;
}

void Date::validDate(const std::string& hour, const std::string& minutes, const std::string& day, const std::string& month, const std::string& year) {
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
        throw std::exception();
    }


    if(dayint < 1 || dayint > 31 || monthint < 0 || monthint > 12 || yearint < 2020 ){
        throw std::exception();
    }
    if(hourint < 0 || hourint > 23 || minutesint < 0 || minutesint > 59)
    {
        throw std::exception();
    }

}

bool Date::operator<(const Date &d) {
    if(this->getYear() > d.getYear())
        return false;

    if(this->getYear() < d.getYear())
        return true;

    if(this->getMonth() > d.getMonth())
        return false;

    if(this->getMonth() < d.getMonth())
        return true;

    if(this->getDay() > d.getDay())
        return false;

    if(this->getDay() < d.getDay())
        return true;

    if(this->getHour() > d.getHour())
        return false;

    if(this->getHour() < d.getHour())
        return true;

    if(this->getMinutes() > d.getMinutes())
        return false;

    if(this->getMinutes() < d.getMinutes())
        return true;

    return true;

}




