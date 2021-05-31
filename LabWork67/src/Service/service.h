# pragma once
#include "../domain/domain.h"
#include "../Repository/repo.h"
#include "../Repository/file_repo.h"
#include "../Store/store.h"
class Service{
private:
    // There will be kept a pointer to the repository and to the storage class.
    IRepo<TElem>* admin_repo;
    IRepo<TElem>* user_repo;
    Abstract_store* storage;

//
public:
    // In order to make the polymorphism work, the fields of the Service class will be
    // initialised with the references of objects repoAdmin, repoUser and _storage.
    // Since repoAdmin and repoUser are objects of type Repo<TElem>, calling the functions of admin_repo/user_repo
    // will call the function with the implementation from that class.
    explicit Service(IRepo<TElem>* repoAdmin, IRepo<TElem>* repoUser, Abstract_store& _storage):admin_repo{repoAdmin}, user_repo{repoUser}, storage{&_storage}{
        storage->write();
    }
    // the copy constructor
    Service(const Service& service);

    ~Service();

    void open();

    IRepo<TElem>& getRepo(const string &mode);

    bool addService(const string& Title, const string& Description, const Date& date, int people, const string& link, const string &mode);
    // The Events will be uniquely identified by the title.
    bool deleteService(const string& title_identifier, const std::string& mode);
    bool updateService(const string& title_identifier, const std::string& field, const Date& date, int people, const string& mode);
    bool incdecPeople(const string& Title,int factor, const string &mode);
    void clear(Service& service, const string& mode);
    static vector<TElem>& sortChronologically(vector<TElem>& elements);
    vector<TElem>& seeAllEvents(const string &mode);
    vector<TElem>& filterEvents(vector<TElem>& filtered_vector, const string& month, const string& mode);


};
