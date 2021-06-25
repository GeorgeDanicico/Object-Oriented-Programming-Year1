#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vector<Weather> w;
    string filename = "weathers.txt";
    Repository repo{ w, filename };
    Service service{ repo };

    GUI ws{service};
    ws.show();
    return a.exec();
}
