#include <observer.h>

#include <sstream>

namespace it
{
namespace testbench
{
namespace data
{

/// SUBJECT

Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::addObserver(Observer* obs)
{
    obsEntities[*(obs->getWhoAmI())] = obs;
    stringstream strStream;
    strStream << obsEntities.count(*(obs->getWhoAmI()));
    DEBUG("Subject::addObserver::Observer Counts ["+*(obs->getWhoAmI())+","+strStream.str()+"]");
}

void Subject::removeObserver(const string* identifier)
{
    if(obsEntities.count(*identifier) == 0)
        return;
    obsEntities.erase(*identifier);
    stringstream strStream;
    strStream << obsEntities.count(*identifier);
    DEBUG("Subject::removeObserver::Observer Counts ["+*identifier+","+strStream.str()+"]");
}

void Subject::notifyObservers(const Report* report)
{
    map<string, Observer*>::iterator mapItr;
    for(mapItr= obsEntities.begin(); mapItr != obsEntities.end(); ++mapItr) {
        Observer* tmpObserver = mapItr->second;
        tmpObserver->notify(report);
        DEBUG("Subject::notifyObservers::Notified ["+mapItr->first+"]");
    }
}

/// OBSERVER

const string* Observer::getWhoAmI() const
{
    return whoAmI;
}

void Observer::setWhoAmI(const string* identifier)
{
    if(identifier->size() == 0)
        return;
    *whoAmI = *identifier;
    DEBUG("Observer::setWhoAmI:: ["+(*whoAmI)+"]");
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
