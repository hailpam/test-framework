#include <support.h>

namespace it
{
namespace testbench
{
namespace data
{

Report::Report() : outcome(false) {}

Report::~Report() {/* pointers to external resources (owned by others) are not deallocated */}

bool Report::getOutcome()
{
    return outcome;
}

void Report::setOutcome(const bool outcome)
{
    this->outcome = outcome;
}

const string* Report::getSessionId()
{
    return sessionId;
}

void Report::setSessionId(const string* sId)
{
    if(sId->size() == 0)
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
    if(tpId->size() == 0)
        return;
    testPlanId = const_cast<string*>(tpId);
    DATA_INFO_VAL("Set Test Plan Id",*testPlanId);
}

const string* Report::getTestId()
{
    return testId;
}

void Report::setTestId(const string* tId)
{
    if(tId->size() == 0)
        return;
    testId = const_cast<string*>(tId);
    DATA_INFO_VAL("Set Test Id",*testId);
}

void Report::setFormattedResorce(FormattedResource* res)
{
    if(res->content.length() == 0 || res->ext.length() == 0 || res->name.length() == 0)
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
