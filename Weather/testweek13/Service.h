#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;
public:
	Service(Repository& repo) : repo(repo) {}
	void addService(string& start, string& end, string& prec, string& desc);
	Repository& getRepo() const { return this->repo; }
	vector<Weather> allWeathers() { return  this->repo.getWeathers();  }
	vector<string> getDiffDesc();
	~Service() = default;
};