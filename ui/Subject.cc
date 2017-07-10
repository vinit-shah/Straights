#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(Observer* observer)
{
    myObservers.push_back(observer);
}

void Subject::unsubscribe(Observer* observer)
{
    myObservers.push_back(observer);
}

void Subject::notify() 
{
    for (std::vector<Observer*>::iterator it = myObservers.begin(); myObservers.end() != it; ++it)
    {
        (*it)->update();
    }
}

