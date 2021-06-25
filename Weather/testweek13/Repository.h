#pragma once
#include "Weather.h"

#include<vector>;

class Repository
{
private:
	vector<Weather>& weathers;
	string& filename;

public:
	Repository(vector<Weather>& w, string& filename) : weathers(w), filename(filename) {
		this->load();
	}
	void addWeather(Weather& w);
	vector<Weather>& getWeathers() const { return this->weathers; }
	void load();
	~Repository() = default;
};