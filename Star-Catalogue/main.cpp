#include <QtWidgets/QApplication>
#include "Window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repo repo{"astronomers.txt", "stars.txt", true};
    Service service{repo};
    vector<Astronomer>& astro = repo.getAstronomers();
    TableModel* model = new TableModel{repo};
    for(auto& e : astro){
        Window* w = new Window{service, e, model};
        service.addObserver(w);
        w->setWindowTitle(QString::fromStdString(e.getName()));
        w->show();
    }


    return a.exec();
}