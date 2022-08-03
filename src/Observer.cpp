#include "Observer.hpp"
#include <iostream>
#include <list>
#include <string>


int Observer::static_number_ = 0;

void Subject::Attach(IObserver *observer)  {
        list_observer_.push_back(observer);
}

void Subject::Detach(IObserver *observer)  {
        list_observer_.remove(observer);
}

void Subject::Notify(int msgid)  {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_,msgid);
            ++iterator;
    }
}

void Subject::CreateMessage(std::string message,int msgid ) {
        this->message_ = message;
        Notify(msgid);
}

Observer::Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        this->number_ = Observer::static_number_;
}

void Observer::Update(const std::string &message_from_subject,int msgid)  {
        msg[msgid]=message_from_subject;
}

    void Observer::RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
}

std::string Observer::getMessage(int msgid) {
    return msg[msgid];
}