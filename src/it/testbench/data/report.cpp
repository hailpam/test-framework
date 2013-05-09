#include <support.h>

namespace it
{
namespace testbench
{
namespace data
{

Report::Report()
{
    sessionId = new string("");
    testPlanId = new string("");
    testId = new string("");
    outcome = false;
}

Report::~Report()
{
    delete sessionId;
    delete testPlanId;
    delete testId;
}

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
    *sessionId = *sId;
    DEBUG("Report::setSessionId::Value Set ["+(*sessionId)+"]");
}

const string* Report::getTestPlanId()
{
    return testPlanId;
}

void Report::setTestPlanId(const string* tpId)
{
    if(tpId->size() == 0)
        return;
    *testPlanId = *tpId;
    DEBUG("Report::setTestPlanId::Value Set ["+(*testPlanId)+"]");
}

const string* Report::getTestId()
{
    return testId;
}

void Report::setTestId(const string* tId)
{
    if(tId->size() == 0)
        return;
    *testId = *tId;
    DEBUG("Report::setTestId::Value Set ["+(*testId)+"]");
}

void Report::setFormattedResorce(FormattedResource* res)
{
    if(res->content.length() == 0 || res->ext.length() == 0 || res->name.length() == 0)
        return;
    resource.content = res->content;
    resource.ext = res->ext;
    resource.name = res->name;
    if(res->hash.length() != 0)
        resource.hash = res->hash;
    DEBUG("Report::setFormattedResorce::Value Set ["<<resource.content<<"||"<<resource.ext<<"||"<<resource.name<<"||"<<resource.hash<<"]");
}

const FormattedResource* Report::getFormattedResource()
{
    return &resource;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
