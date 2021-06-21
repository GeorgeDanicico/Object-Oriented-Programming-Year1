//
// Created by georg on 6/21/2021.
//

#include "test.h"
#include <assert.h>

void test::test_all() {
    Repo repo{"users.txt", "issues.txt"};

    Service serv{repo};

    Issue i{"fatal", "open", "Sergiu", ""};
    assert(serv.add_issue(i) == false);
    Issue i2{"keylogger", "open", "Sergiu", ""};
    assert(serv.add_issue(i2) == true);

    Issue i3{"mvc", "closed", "Andrew", "Arthur"};
    Issue i4{"kinect", "closed", "Andrew", "Arthur"};

    serv.modify(i3);
    serv.modify(i4);

    vector<Issue> v = repo.getIssues();
    auto it = find_if(v.begin(), v.end(), [](Issue& i){
        return i.getDescription() == "kinect";
    });

    assert((*it).getSolver() == "Arthur");
}
