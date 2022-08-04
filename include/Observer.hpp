#ifndef OBSERVER_HPP
#define OBSERVER_HPP


#include <iostream>
#include <list>
#include <string>
#include<map>

using namespace std;

#define TRACKNAME_MSG 0
#define LIFE_MSG 1
#define TRACK_MSG 2
#define MONEY_MSG 3


class IObserver {
public:
    virtual void Update(const std::string &message_from_subject,int msgid) = 0;
};

class ISubject {
public:
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify(int msgid) = 0;
};

class Subject : public ISubject {
public:
    void Attach(IObserver *observer) override;
    void Detach(IObserver *observer) override;
    void Notify(int msgid) override;
    void CreateMessage(std::string message = "Empty",int msgid=0);

private:
    std::list<IObserver *> list_observer_;
    std::string message_;
};

class Observer : public IObserver {
public:
    Observer(Subject &subject);
    void Update(const std::string &message_from_subject, int msgid) override ;
    void RemoveMeFromTheList();
    std::string getMessage(int msgid);

private:
    std::string message_from_subject_;
    std::string msglife;
    std::map <int,std::string> msg;
    Subject &subject_;
    static int static_number_;
    int number_;
};

#endif //OBSERVER_HPP
