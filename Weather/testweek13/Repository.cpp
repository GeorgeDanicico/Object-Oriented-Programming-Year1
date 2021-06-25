#include<fstream>

#include "Repository.h"

void Repository::addWeather(Weather& w)
{
	this->weathers.push_back(w);
}

void Repository::load()
{
	ifstream fin(this->filename, ios::in);
	string start, end, prec, desc;
	string line;
	while (getline(fin, line)) {
		string token;
		size_t position = line.find(';');
		token = line.substr(0, position);
		start = token;
		line.erase(0, position + 1);

		position = line.find(';');
		token = line.substr(0, position);
		end = token;
		line.erase(0, position + 1);

		position = line.find(';');
		token = line.substr(0, position);
		prec = token;
		line.erase(0, position + 1);

		position = line.find(';');
		token = line.substr(0, position);
		desc = token;
		line.erase(0, position + 1);


		Weather w{ start, end, prec, desc };
		this->addWeather(w);
	}
}
