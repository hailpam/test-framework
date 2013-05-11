#include <observer.h>

#include <sstream>

namespace it
{
namespace testbench
{
namespace data
{

/// SUBJECT

Subject::Subject() {/* Do nothing */}

Subject::~Subject() {/* Do nothing */}

ReturnCode Subject::addObserver(Observer* obs)
{
    ReturnCode retCond;
    if(obs == 0) {
        DATA_ERR_VAL("NULL Pointer", obs);
        retCond.code = ERROR;
        retCond.desc = "Null Point for the Observer";

        return retCond;
    }
    //
    DATA_INFO_VAL("Setting the Observer", obs->getWhoAmI());
    obsEntities[obs->getWhoAmI()] = obs;
    DATA_INFO_VAL("Observer Count", obsEntities.size());
    //
    retCond.code = SUCCESS;
    retCond.desc = "Observer correctly registered";
    //
    return retCond;
}

ReturnCode Subject::removeObserver(const string& identifier)
{
    ReturnCode retCond;
    if(obsEntities.count(identifier) == 0) {
        DATA_ERR_VAL("Observer not present", identifier);
        retCond.code = ERROR;
        retCond.desc = "Blanck Identifier in Input";

        return retCond;
    }
    DATA_INFO_VAL("Removing the Observer", identifier);
    obsEntities.erase(identifier);
    DATA_INFO_VAL("Observer Count", obsEntities.size());
    //
    retCond.code = SUCCESS;
    retCond.desc = "Observer correctly registered";
    //
    return retCond;
}

void Subject::notifyObservers(Report* report)
{
    for(mapItr= obsEntities.begin(); mapItr != obsEntities.end(); ++mapItr) {
        Observer* tmpObserver = mapItr->second;
        DATA_INFO_VAL("Notifying the Observer", tmpObserver->getWhoAmI());
        tmpObserver->notify(report);
        DATA_INFO_VAL("Observer Notified with Report", report->getTestPlanId());
    }
}

/// OBSERVER

const string& Observer::getWhoAmI() const
{
    return whoAmI;
}

void Observer::setWhoAmI(const string& identifier)
{
    if(identifier.size() == 0) {
        DATA_ERR_VAL("Emptry String provided in input", identifier);
        return;
    }
    whoAmI = identifier;
    DATA_INFO_VAL("Setting Observer Identifier",whoAmI);
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
