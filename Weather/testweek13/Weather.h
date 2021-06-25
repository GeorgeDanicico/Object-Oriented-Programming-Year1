#pragma once
#include<string>

using namespace std;

class Weather
{
private:
	string starting_date, ending_date, precipitation, description;
public:
	Weather(string &start, string& end, string& precipitation, string& description) : starting_date(start), ending_date(end), precipitation(precipitation), description(description){}
	string getStarting() { return this->starting_date; }
	string getEnding() { return this->ending_date; }
	string getPrec() { return this->precipitation; }
	string getDesc() { return this->description; }
	
	~Weather()=default;



};

