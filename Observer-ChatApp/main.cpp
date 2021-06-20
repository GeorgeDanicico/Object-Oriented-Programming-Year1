#include <QtWidgets/QApplication>
#include "ChatWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    User user1{string("lion.png"), string("chris123")};
    User user2{string("bear.png"), string("beerr123")};
    User user3{string("tiger.jpeg"), string("bob123")};
    ChatSession session{};

    ChatWindow chris{session, user1};
    chris.show();
    ChatWindow beerr{session, user2};
    beerr.show();
    ChatWindow bob{session, user3};
    bob.show();

    return a.exec();
}