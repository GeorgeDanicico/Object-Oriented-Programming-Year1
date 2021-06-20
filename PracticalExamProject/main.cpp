#include <QtWidgets/QApplication>
#include "ProgWindow.h"
#include "Table.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repo repo{"programmers.txt", "sourcefile.txt"};
    Service serv {repo};
    vector<Programmer> programmers = repo.getProgrammers();

    TableModel* table = new TableModel{repo};
    for(auto& e : programmers){
        ProgWindow* p = new ProgWindow{serv, e, table};
        serv.addObserver(p);
        p->show();
    }

    return a.exec();
}