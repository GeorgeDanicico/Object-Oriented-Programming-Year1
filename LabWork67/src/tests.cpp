#pragma once
#include <fstream>
#include<iostream>
#include"domain/domain.h"
#include"Repository/repo.h"
#include "Service/service.h"
#include "Repository/file_repo.h"
#include "Store/store_html.h"
#include <cassert>
#include <exception>
#include<vector>

using namespace std;

void test_date(){
    Date data{ 22, 30,1,3,2020 };

    Date data1{data};
    assert(data.getHour() == 22);
    assert(data.getMinutes() == 30);
    assert(data.getDay() == 1);
    assert(data.getMonth() == 3);
    assert(data.getYear() == 2020);
    try{
        Validation::validDate("22", "30", "1", "3", "2020");
        Validation::validDate("22", "70", "1", "3", "2020");
    }
    catch(std::exception& e){}
    try{
        Validation::validDate("22", "30", "1", "3", "2020");
        Validation::validDate("22", "20", "1", "3", "2019");
    }
    catch(std::exception& e){}
    try{
        Validation::validDate("22a", "30", "1", "3", "2020");
    }
    catch(std::exception& e){}

    Date data2{20, 21, 12, 11, 2020};
    Date data3{20, 21, 12, 12, 2020};

    assert(data3 < data2 == false);
    assert(data2 < data3 == true);
    assert((data < data1) == true);

    Date data4{20, 21, 11, 12, 2020};
    Date data5{20, 21, 12, 12, 2020};
    assert(data4 < data5 == true);
    assert(data5 < data4 == false);

    Date data6{20, 20, 12, 12, 2020};
    Date data7{20, 21, 12, 12, 2020};
    assert(data6 < data7 == true);
    assert(data7 < data6 == false);

    Date data8{19, 21, 12, 12, 2020};
    Date data9{20, 21, 12, 12, 2020};
    assert(data8 < data9 == true);
    assert(data9 < data8 == false);
    std::cout<<"Testing Date successfully!\n";
}

void test_domain() {

    Event event0;
    Date data{ 22, 30,1,3,2020 };
	Event event1{ "Your title", "Very nice movie", data, 190, "www.prost.com" };
	Event event2 = event1;
	assert(event2.getPeopleNr() == event1.getPeopleNr());

	assert(event1.getDescription() == "Very nice movie");
    assert(event1.getLink() == "www.prost.com");
	Event* event3;
	event3 = new Event( "Your title", "beautiful", data, 190, "www.prost.com" );
	Event event4 = *event3;
	assert(event4.getTitle() == event3->getTitle());

	std::ofstream fout("event.out");
	fout << event4;
	fout.close();
    event2.updateDate(data);
    event2.updatePeople(20);

	// we check if the copy constructor works.
	assert(&event4 != event3);
	Date d = event1.getDate();
	Date d2 = event3->getDate();
	//std::cout << d.getDay();
	delete event3;
    std::cout<<"Testing Domain successfully!\n";
}

void test_DA() {
    vector<TElem> dynamicArray;

	Date data{ 22, 30,1,3,2020 };
	TElem element1{"Your title", "beautiful", data, 190, "www.prost.com"};

	assert(dynamicArray.size() == 0);

    dynamicArray.push_back(element1);
	assert(dynamicArray.size() == 1);
	TElem element2{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element3{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element4{"Your title", "beautiful", data, 190, "www.prost.com"};

	dynamicArray.push_back(element2);
    dynamicArray.push_back(element3);
    dynamicArray.push_back(element4);

    auto it1 = find(dynamicArray.begin(), dynamicArray.end(), element1);

    assert(*it1 == element1);

    TElem new_element1 = dynamicArray[1];

    TElem Element{"your title", "beautiful", data, 190, "www.prost.com"};

    auto it2 = find(dynamicArray.begin(), dynamicArray.end(), Element);
    assert(it2 == dynamicArray.end());


    auto it = dynamicArray.begin();
    dynamicArray.erase(it);
    assert(dynamicArray.size() == 3);
	TElem element5{"MY TITLE", "beautiful", data, 190, "www.prost.com"};
	dynamicArray[1] = element5;

	assert(dynamicArray.size() == 3);
	assert(dynamicArray[1].getTitle() == "MY TITLE");

    std::cout<<"Testing STL Vector successfully!\n";
}

void test_repo() {
    std::string file = "../events.out";
    std::string file2 = "";
    vector<TElem> dV, dV2, dV3;
	Repo<TElem> repo{dV, file};
    Repo<TElem> repo3{dV2, ""};

	Date data{ 22, 30,1,3,2020 };
	TElem element1{"Your title", "beautiful", data, 190, "www.prost.com"};

	assert(repo.size() == 0);
    repo.add(element1);
	assert(repo.size() == 1);
	TElem element2{"Your title1", "beautiful", data, 190, "www.prost.com"};
	TElem element3{"Your title2", "beautiful", data, 190, "www.prost.com"};
	TElem element4{"Your title3", "beautiful", data, 190, "www.prost.com"};
	TElem element5{"My Title", "beautiful", data, 190, "www.prost.com"};
//
	vector<TElem> elements = repo.get_all();
//
	assert(elements[0].getTitle() == "Your title");
//
//
    repo.add(element2);
    repo.add(element3);
    repo.add(element4);
	assert(repo.size() == 4);
//
	auto it = dV.begin();
	it++;
	repo.remove(element1);
	assert(repo.size() == 3);
	repo.update(element5, 1);
    TElem element6{"My Title1", "beautiful", data, 190, "www.prost.com"};
    TElem element7{"My Title2", "beautiful", data, 190, "www.prost.com"};
    TElem element8{"My Title3", "beautiful", data, 190, "www.prost.com"};

//
    repo3.add(element7);
    repo3.add(element6);
    repo3.update(element8, 0);
    auto it1 = dV2.begin();
    repo3.remove(element8);
//
	assert(repo.get_element(1).getTitle() == "My Title");
//
    std::ofstream fout(file);
    fout << "";
    fout.close();
	std::cout << "Testing Repository successfully!\n";
}

void test_service(){
    std::string file;
    std::string file2;
    vector<TElem> dV, dV2;
    Repo<TElem> repo{dV, file};
    Repo<TElem> repo2{dV2, file2};
    Store_html html{dV, ""};
    Service new_service{&repo, &repo2, html};
    Date date{12,12,12,12,2021};
//
    Service copy = new_service;
//
    new_service.addService("My title", "Description", date, 20, "link", "admin");
    assert (new_service.addService("My title", "Description", date, 20, "link", "admin") == false);
    Date date1{12,12,12,12,2026};
    Date date2{12,12,12,12,2024};
    Date date3{12,12,12,12,2023};
    new_service.addService("My title 1", "Description", date1, 20, "link", "admin");
    new_service.addService("My title 2", "Description", date2, 20, "link", "admin");
    new_service.addService("My title 3", "Description", date3, 20, "link", "admin");

//
    int length = 0;
    vector<TElem> filter(dV.size());
//    vector<TElem>& new_list = new_service.filterEvents(filter, "12", "admin");
//
//    assert(new_list.size() == 4);
//
    new_service.incdecPeople("My title 2", 1, "admin");
    assert(new_service.incdecPeople("ma iubesti", 1, "admin") == false);
    assert(new_service.updateService("My title 3", "people", date2, 330, "admin") == true);
    assert(new_service.updateService("My title 3", "date", date2, 330, "admin") == true);
    assert(new_service.updateService("My title 331231321", "date", date2, 330, "admin") == false);
////
    assert(new_service.addService("My title 3", "Description", date3, 331, "link", "user") == true);
//
    try{
        new_service.addService("", "Description", date, 20, "link", "admin");

    }catch(std::exception& e){}
////
    assert(new_service.getRepo("admin").size() == 4);
    assert(new_service.updateService("My title 3", "people", date1, 230, "admin") == true);

//
//    vector<TElem>& elem2 = new_service.seeAllEvents("user");

//    TElem* elem = new_service.sortChronologically(new_list, 4);
    new_service.deleteService("My title", "admin");
    new_service.deleteService("My title 3", "admin");
//
    assert(dV.size() == 2);
////
    assert(new_service.deleteService("My title", "admin") == false);
//    Service service2{repo, repo2, html};
//    new_service.clear(service2, "admin");
    std::cout << "Testing Service successfully!\n";
}

void all_tests() {
    test_date();
	test_domain();
	test_DA();
	test_repo();
	test_service();
	std::cout << "Tests executed succesfully!.\n";
}