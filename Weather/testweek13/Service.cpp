#include "Service.h"
#include <algorithm>

void Service::addService(string& start, string& end, string& prec, string& desc)
{
	Weather w{ start, end, prec, desc };
	this->repo.addWeather(w);
}

vector<string> Service::getDiffDesc()
{
	vector<string> descriptions;

	vector<Weather> copy = this->repo.getWeathers();

	for (int i = 0; i < copy.size(); i++) {
		bool found = false;
		string desc;
		for (int j = 0; j < descriptions.size() && found == false; j++) {
			if (descriptions[j] == copy[i].getDesc())
				found = true;
		}

		if (found == false) {
			descriptions.push_back(copy[i].getDesc());
		}
	}



	return descriptions;
}
