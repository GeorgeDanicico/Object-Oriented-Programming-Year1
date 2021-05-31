# pragma once
#include "repo.h"

class Service{
private:
    Repository& admin_repo;
    Repository& user_repo;
//
public:
    Service(Repository& repoAdmin, Repository& repoUser):admin_repo{repoAdmin}, user_repo{repoUser}{}
    // the copy constructor
   Service(const Service& service);

    ~Service();

    Repository& getRepo(const std::string &mode);

    bool addServiceElement(std::string Title,std::string Description, Date date, int people, std::string link,  const std::string &mode);
    // The movie will be uniquely identified by the title
    bool deleteServiceElement(std::string title_indentifier, const std::string& mode);
    bool updateServiceElement(std::string title_identifier, std::string field, Date date, int people, const std::string& mode);

    bool incdecPeople(std::string Title,int factor, const std::string &mode);

    void clear(Service& service, const std::string& mode);

    static TElem* sortChronologically(TElem* elements, const int& length);

    TElem* seeAllEvents(const std::string &mode);
    TElem* filterEvents(std::string month, int &length, const std::string& mode);


};
