# pragma once
#include "repo.h"

class Service{
private:
    Repository& repo;
//
public:
    Service(Repository& repository):repo{repository}{}
    // the copy constructor
//   Service(const Service& admin_service);

    ~Service();

    Repository& getRepo(){ return this->repo; };

    bool addServiceElement(std::string Title,std::string Description, Date date, int people, std::string link);
    // The movie will be uniquely identified by the title
    bool deleteServiceElement(std::string title_indentifier);
    bool updateServiceElement(std::string title_identifier, std::string field, Date date, int people);

    bool incdecPeople(std::string Title,int factor);

    void clear(Service& service);

    static TElem* sortChronologically(TElem* elements, const int& length);

    TElem* seeAllEvents(){ return this->repo.getRepoElements(); };
    TElem* filterEvents(std::string month, int &length);


};
