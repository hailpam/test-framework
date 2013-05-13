#include <support.h>

namespace it
{
namespace testbench
{
namespace data
{

Report::Report()
{
    sessionId = 0;
    testPlanId = 0;
    testId = 0;
    retCodes = 0;
    resource = 0;
}

Report::~Report() {/* pointers to external resources (owned by others) are not deallocated */}

list<ReturnCode*>* Report::getOutcome()
{
    return retCodes;
}

void Report::setOutcome(list<ReturnCode*>* outcome)
{
    this->retCodes = outcome;
}

const string* Report::getSessionId()
{
    return sessionId;
}

void Report::setSessionId(const string* sId)
{
    if (!sId || sId->size() == 0)
        return;
    sessionId = const_cast<string*>(sId);
    DATA_INFO_VAL("Set Session Id",*sessionId);
}

const string* Report::getTestPlanId()
{
    return testPlanId;
}

void Report::setTestPlanId(const string* tpId)
{
    if (!tpId || tpId->size() == 0)
        return;
    testPlanId = const_cast<string*>(tpId);
    DATA_INFO_VAL("Set Test Plan Id",*testPlanId);
}

const unsigned int Report::getTestId()
{
    return testId;
}

void Report::setTestId(const unsigned int tId)
{
    testId = tId;
    DATA_INFO_VAL("Set Test Id", testId);
}

void Report::setFormattedResorce(FormattedResource* res)
{
    if (!res || res->content.length() == 0 || res->ext.length() == 0 || res->name.length() == 0)
        return;
    resource = const_cast<FormattedResource*>(res);
    DATA_INFO_VAL("Pointer Associated",resource);
}

const FormattedResource* Report::getFormattedResource()
{
    return resource;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
