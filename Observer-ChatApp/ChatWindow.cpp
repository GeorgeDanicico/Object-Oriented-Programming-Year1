//
// Created by georg on 6/20/2021.
//

#include "ChatWindow.h"

void ChatWindow::update() {
    this->populateList();
}

void ChatWindow::populateList() {
    this->repository->clear();

    vector<pair<Message, User>>& m = this->session.getMessages();
    for(auto message : m){
        string info = message.first.getMessage();
        string username = message.second.getName();
        QFont serifFont("Times", 20, QFont::Bold);
        if(username == this->user.getName()){
            string row = "[Me]: " + info;
            QListWidgetItem* lwi = new QListWidgetItem(QString(QString::fromStdString(row)));
            this->repository->addItem(lwi);
            lwi->setTextAlignment(Qt::AlignRight);
            lwi->setIcon(QIcon(QString::fromStdString(this->user.getPhoto())));
            lwi->setForeground(Qt::red);

        }
        else{
            string row = "[" + username + "]: " + info;
            QListWidgetItem* lwi = new QListWidgetItem(QString(QString::fromStdString(row)));
            this->repository->addItem(lwi);
            lwi->setIcon(QIcon(QString::fromStdString(message.second.getPhoto())));
            lwi->setTextAlignment(Qt::AlignLeft);
        }

    }
}

void ChatWindow::sendMessageFunc() {

    string message = this->myMessage->text().toStdString();
    if(message != ""){
        message.erase(0, message.find(':')+1);
        Message new_message{message};
        User new_user{user.getPhoto(), user.getName()};
        this->session.addMessage(new_user, new_message);
        this->myMessage->clear();
    }
    else return;
}
