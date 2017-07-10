#pragma once

#include <vector>

class Observer;

class Subject
{
    public:
        void subscribe(Observer*);
        void unsubscribe(Observer*);
        void notify();
    private:
        std::vector<Observer*> myObservers;
};
