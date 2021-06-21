#include <QtWidgets/QApplication>
#include "Window.h"
#include "test.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test::test_all();

    Repo repo{"users.txt", "issues.txt", true};

    Service serv{repo};
    vector<User> users = repo.getUsers();
    TableModel* model = new TableModel{repo};
    for(auto& u : users){
        Window* w = new Window{serv, u, model};
        w->setWindowTitle(QString::fromStdString(u.getName() + "/" + u.getType()));
        w->show();
        serv.addObserver(w);
    }


    return a.exec();
}