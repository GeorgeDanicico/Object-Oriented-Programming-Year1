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




