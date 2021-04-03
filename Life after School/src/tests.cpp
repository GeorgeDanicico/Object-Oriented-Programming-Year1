#pragma once
#include <fstream>
#include<iostream>
#include"domain.h"
#include"dynamicArray.h"
#include"repo.h"
#include "service.h"
#include <cassert>
#include <exception>

void test_date(){
    Date data{ 22, 30,1,3,2020 };

    Date data1{data};
    assert(data.getHour() == 22);
    assert(data.getMinutes() == 30);
    assert(data.getDay() == 1);
    assert(data.getMonth() == 3);
    assert(data.getYear() == 2020);
    try{
        Date::validDate("22", "30", "1", "3", "2020");
        Date::validDate("22", "70", "1", "3", "2020");
    }
    catch(std::exception& e){}
    try{
        Date::validDate("22", "30", "1", "3", "2020");
        Date::validDate("22", "20", "1", "3", "2019");
    }
    catch(std::exception& e){}
    try{
        Date::validDate("22a", "30", "1", "3", "2020");
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
	DynamicVector<TElem> dynamicArray;
	Date data{ 22, 30,1,3,2020 };
	TElem element1{"Your title", "beautiful", data, 190, "www.prost.com"};

	DynamicVector<TElem> b;


	assert(dynamicArray.size() == 0);
	assert(dynamicArray.getCapacity() == 2);

    dynamicArray.add(element1);
    b = dynamicArray;
	assert(dynamicArray.size() == 1);
	TElem element2{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element3{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element4{"Your title", "beautiful", data, 190, "www.prost.com"};
    dynamicArray.add(element2);
    dynamicArray.add(element3);
    dynamicArray.add(element4);

    TElem new_element1 = dynamicArray[1];

    dynamicArray.remove(0);
    assert(dynamicArray.size() == 3);
    assert(dynamicArray.getCapacity() == 4);
	TElem element5{"MY TITLE", "beautiful", data, 190, "www.prost.com"};
	dynamicArray.updateEvent(element5, 1);

	assert(dynamicArray.size() == 3);
	assert(dynamicArray[1].getTitle() == "MY TITLE");

    std::cout<<"Testing Dynamic Vector successfully!\n";
}

void test_repo() {
    std::string file = "../events.out";
    std::string file2 = "";
    DynamicVector<TElem> dV, dV2, dV3;
	Repository repo{dV, file};
    Repository repo3{dV2, ""};

	Date data{ 22, 30,1,3,2020 };
	TElem element1{"Your title", "beautiful", data, 190, "www.prost.com"};

	assert(repo.getRepoSize() == 0);
	repo.addRepoElement(element1);
	assert(repo.getRepoSize() == 1);
	TElem element2{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element3{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element4{"Your title", "beautiful", data, 190, "www.prost.com"};
	TElem element5{"My Title", "beautiful", data, 190, "www.prost.com"};

	TElem* elements = repo.getRepoElements();

	Repository repo2{dV2, file};

	repo.addRepoElement(element2);
	repo.addRepoElement(element3);
	repo.addRepoElement(element4);
	assert(repo.getRepoSize() == 4);
	repo.deleteRepoElement(1);
	assert(repo.getRepoSize() == 3);
	repo.updateRepoElement(element5, 1);
    TElem element6{"My Title", "beautiful", data, 190, "www.prost.com"};
    TElem element7{"My Title", "beautiful", data, 190, "www.prost.com"};
    TElem element8{"My Title", "beautiful", data, 190, "www.prost.com"};


    repo3.addRepoElement(element7);
    repo3.addRepoElement(element6);
    repo3.updateRepoElement(element8, 0);
    repo3.deleteRepoElement(0);

	assert(repo.getRepoElement(1).getTitle() == "My Title");
//
    std::ofstream fout(file);
    fout << "";
    fout.close();
	std::cout << "Testing Repository successfully!\n";
}

void test_service(){
    std::string file;
    std::string file2;
    DynamicVector<TElem> dV, dV2;
    Repository repo{dV, file};
    Repository repo2{dV2, file2};
    Service new_service{repo, repo2};
    Date date{12,12,12,12,2021};

    Service copy = new_service;

    new_service.addServiceElement("My title", "Description", date, 20, "link", "admin");
    assert (new_service.addServiceElement("My title", "Description", date, 20, "link", "admin") == false);
    Date date1{12,12,12,12,2026};
    Date date2{12,12,12,12,2024};
    Date date3{12,12,12,12,2023};
    new_service.addServiceElement("My title 1", "Description", date1, 20, "link", "admin");
    new_service.addServiceElement("My title 2", "Description", date2, 20, "link", "admin");
    new_service.addServiceElement("My title 3", "Description", date3, 20, "link", "admin");


    int length = 0;
    TElem* new_list = new_service.filterEvents("12", length, "admin");
    assert(length == 4);

    try{
        new_list = new_service.filterEvents("aa", length, "admin");
    }
    catch(std::exception& e){}

    new_service.incdecPeople("My title 2", 1, "admin");
    assert(new_service.incdecPeople("ma iubesti", 1, "admin") == false);
    assert(new_service.updateServiceElement("My title 3", "people", date2, 330, "admin") == true);
    assert(new_service.updateServiceElement("My title 3", "date", date2, 330, "admin") == true);
    assert(new_service.updateServiceElement("My title 331231321", "date", date2, 330, "admin") == false);

    assert(new_service.addServiceElement("My title 3", "Description", date3, 331, "link", "user") == true);

    try{
        new_service.addServiceElement("", "Description", date, 20, "link", "admin");

    }catch(std::exception& e){}

    assert(new_service.getRepo("admin").getRepoSize() == 4);

    assert(new_service.updateServiceElement("My title 3", "people", date1, 230, "admin") == true);

    TElem* elem2 = new_service.seeAllEvents("admin");
    elem2 = new_service.seeAllEvents("user");
    TElem* elem = new_service.sortChronologically(new_list, 4);
    delete[] new_list;
    new_service.deleteServiceElement("My title", "admin");
    new_service.deleteServiceElement("My title 3", "admin");

    assert(new_service.getRepo("admin").getRepoSize() != 4);
    assert(new_service.deleteServiceElement("My title", "admin") == false);
    Service service2{repo, repo2};
    new_service.clear(service2, "admin");
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