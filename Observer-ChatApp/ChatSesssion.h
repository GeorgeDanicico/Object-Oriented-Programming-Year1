//
// Created by georg on 6/20/2021.
//

#pragma once
#include "Observers.h"
#include "UserMessage.h"

class ChatSession : public Subject{
private:
    vector<pair<Message, User>> messages;
public:

    void addMessage(User u, Message m){
        pair<Message, User> p(m, u);
        messages.push_back(p);
        this->notify();
    }
    vector<pair<Message, User>>& getMessages() {return messages;}
    ~ChatSession()=default;
};


