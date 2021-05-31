#include<iostream>
#include "date.h"
#include "domain.h"
#include "Exception.h"

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

Date::Date(string token)
{
    try {
        string hour, minutes, day, month, year;
        hour = token.substr(0, token.find('/'));
        token.erase(0, token.find('/') + 1);
        minutes = token.substr(0, token.find('/'));
        token.erase(0, token.find('/') + 1);
        day = token.substr(0, token.find('/'));
        token.erase(0, token.find('/') + 1);
        month = token.substr(0, token.find('/'));
        token.erase(0, token.find('/') + 1);
        year = token.substr(0, token.find(';'));
        Validation::validDate(hour, minutes, day, month, year);
        this->hour = stoi(hour);
        this->minutes = stoi(minutes);
        this->day = stoi(day);
        this->month = stoi(month);
        this->year = stoi(year);
    }
    catch (ImplementedException& e) {
        throw ImplementedException(e.what());
    }
}

Date::~Date() = default;

// we overload the operate = in order to swap dates easily
Date &Date::operator=(const Date &d) = default;

bool Date::operator<(const Date &d) const {
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

bool Date::operator==(const Date &d) const {
    if(this->hour  != d.hour)
        return false;
    if(this->day  != d.day)
        return false;
    if(this->minutes  != d.minutes)
        return false;
    if(this->month  != d.month)
        return false;
    if(this->year  != d.year)
        return false;

    return true;
}

ostream &operator<<(ostream &os, const Date &date) {
    os << date.getHour() << "/" << date.getMinutes() << "/" << date.getDay() << "/"
    << date.getMonth() << "/" << date.getYear();

    return os;
}




