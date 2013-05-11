#include <custom_testitems.h>

namespace it
{
namespace testbench
{
namespace data
{

CustomSetupItem::CustomSetupItem() {}
TestCaseContext* CustomSetupItem::setupItem()
{
    A* aVar = new A();
    B* bVar = new B();
    ConcreteContextObject* ctxObj = new ConcreteContextObject();
    string* myDescription = new string("MyFavouriteDescription");
    ctxObj->setDescription(myDescription);
    ctxObj->setA(aVar);
    ctxObj->setB(bVar);

    DEBUG("CustomSetupItem::setupItem ["+*(ctxObj->getDescription())+"]");

    return ctxObj;
}

CustomRunnableTestItem::CustomRunnableTestItem() {}
Report* CustomRunnableTestItem::runItem(const TestCaseContext* ctxObject)
{
    DEBUG("CustomRunnableTestItem::runItem ["+*(ctxObject->getDescription())+"]");

    Report* report = new Report();
    string* sessionId = new string("MySessionId");
    report->setSessionId(sessionId);
    //
    string* testPlanId = new string("MyTestPlanId");
    report->setTestPlanId(testPlanId);
    //
    string* testId = new string("MyTestId");
    report->setTestId(testId);
    //
    report->setOutcome(true);

    return report;
}

CustomTearDownTestItem::CustomTearDownTestItem() {}
void CustomTearDownTestItem::tearDownItem(TestCaseContext* ctxObject)
{
    DEBUG("CustomTearDownTestItem::tearDownItem ["+*(ctxObject->getDescription())+"]");

    delete (ConcreteContextObject*) ctxObject;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
