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
    string myDescription = "MyFavouriteDescription";
    ctxObj->setDescription(myDescription);
    ctxObj->setA(aVar);
    ctxObj->setB(bVar);
    DATA_INFO_VAL("Setup Accomplished", ctxObj->getDescription());

    return ctxObj;
}

CustomRunnableTestItem::CustomRunnableTestItem() {}
Report* CustomRunnableTestItem::runItem(TestCaseContext* ctxObject)
{
    DATA_INFO_VAL("Running the Test Ite", ctxObject->getDescription());

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
    DATA_INFO_VAL("Tear Down Accomplished", ctxObject->getDescription());
    if(ctxObject != 0)
        delete (ConcreteContextObject*) ctxObject;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
