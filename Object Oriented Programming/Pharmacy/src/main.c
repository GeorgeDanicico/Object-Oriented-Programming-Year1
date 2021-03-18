#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ui.h"
#include "tests.h"
#include <crtdbg.h>
#include <stdlib.h>

int main() {
    all_tests();

    Repo* repo = createRepo();
    Service* service = createService(repo);
    UI* ui = createUI(service);

    setEntries(ui);

    start(ui);
    destroyUI(ui);
    
    if (!_CrtDumpMemoryLeaks()) {
        printf("\nCongratulation, no memory leaks!\n");
    }
    else {
        printf("\nOoopsie, there are some leaks.\n");
    }
   


    return 0;
}
