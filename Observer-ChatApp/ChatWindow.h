//
// Created by georg on 6/20/2021.
//
#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "ChatSesssion.h"
#include <qlayout.h>
#include <qfont.h>


class ChatWindow : public QWidget, public Observer{
private:
    ChatSession& session;
    User& user;
    QListWidget* repository;
    QPushButton* sendMessage;
    QLineEdit* myMessage;
    QVBoxLayout* mainLayout;
public:
    ChatWindow(ChatSession& s, User& u):session{s}, user{u}{
        this->setWindowTitle(QString::fromStdString(user.getName()));
        mainLayout = new QVBoxLayout{this};
        repository = new QListWidget{};
        sendMessage = new QPushButton{"Send"};
        myMessage = new QLineEdit{};

        mainLayout->addWidget(repository);
        QGridLayout* grid = new QGridLayout{};
        grid->addWidget(myMessage,0 ,0);
        grid->addWidget(sendMessage,0 ,1);
        mainLayout->addLayout(grid);

        this->session.addObserver(this);
        emit populateList();

        QObject::connect(this->sendMessage, &QPushButton::clicked, this, [this](){
            emit this->sendMessageFunc();
        });
    }

    void populateList();
    void update() override;
    void sendMessageFunc();
    ~ChatWindow()=default;
};



