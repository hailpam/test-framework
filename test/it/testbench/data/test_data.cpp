#include <support.h>
#include <observer.h>
#include <fake_observer.h>
#include <concrete_ctxobject.h>
#include <custom_testitems.h>

#include <iostream>

using namespace std;

using namespace it::testbench::data;

int main(int argc, char* argv[])
{
    /// REPORT TEST
    Report* report = new Report();
    string* sessionId = new string("MySessionId");
    report->setSessionId(sessionId);
    cout << "Test [" << ((sessionId->compare(*(report->getSessionId())) == 0)?"PASS":"FAIL") << "]" << endl;
    //
    string* testPlanId = new string("MyTestPlanId");
    report->setTestPlanId(testPlanId);
    cout << "Test [" << ((testPlanId->compare(*(report->getTestPlanId())) == 0)?"PASS":"FAIL") << "]" << endl;
    //
    string* testId = new string("MyTestId");
    report->setTestId(testId);
    cout << "Test [" << ((testId->compare(*(report->getTestId())) == 0)?"PASS":"FAIL") << "]" << endl;
    //
    FormattedResource res;
    res.ext = "TEXT";
    res.content = "aahahahahhahahahahaah";
    res.name = "blah";
    res.hash = "";
    report->setFormattedResorce(&res);
    cout << "Test [" << ((res.content.compare(report->getFormattedResource()->content) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "Test [" << ((res.ext.compare(report->getFormattedResource()->ext) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "Test [" << ((res.hash.compare(report->getFormattedResource()->hash) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "Test [" << ((res.name.compare(report->getFormattedResource()->name) == 0)?"PASS":"FAIL") << "]" << endl;

    /// OBSERVER TEST
    string* obsId1 = new string("Observer#1");
    string* obsId2 = new string("Observer#2");
    FakeObserver* fakeObs1 = new FakeObserver();
    FakeObserver* fakeObs2 = new FakeObserver();
    fakeObs1->setWhoAmI(obsId1);
    fakeObs2->setWhoAmI(obsId2);
    cout << "Test [" << ((obsId1->compare(*(fakeObs1->getWhoAmI())) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "Test [" << ((obsId2->compare(*(fakeObs2->getWhoAmI())) == 0)?"PASS":"FAIL") << "]" << endl;
    /// SUBJECT TEST
    Subject* aSubject = new Subject();
    aSubject->addObserver(fakeObs1);
    aSubject->addObserver(fakeObs2);
    aSubject->notifyObservers(report);

    /// CONCRETE CONTEXT OBJECT
    A* aVar = new A();
    B* bVar = new B();
    ConcreteContextObject* ctxObj = new ConcreteContextObject();
    string* myDescription = new string("MyFavouriteDescription");
    ctxObj->setDescription(myDescription);
    cout << "Test [" << ((ctxObj->getDescription()->compare(*myDescription) == 0)?"PASS":"FAIL") << "]" << endl;
    ctxObj->setA(aVar);
    ctxObj->setB(bVar);
    string tmp1 = aVar->getAString();
    string tmp2 = bVar->getBString();
    string tmp3 = ctxObj->getA()->getAString();
    string tmp4 = ctxObj->getB()->getBString();
    cout << "Test [" << ((tmp1.compare(tmp3) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "Test [" << ((tmp2.compare(tmp4) == 0)?"PASS":"FAIL") << "]" << endl;

    /// TEST ITEMs
    CustomSetupItem* cSetItem = new CustomSetupItem();
    TestCaseContext* tcCtx = cSetItem->setupItem();
    string tmp5 = *(tcCtx->getDescription());
    cout << "Test [" << ((tmp5.compare("MyFavouriteDescription") == 0)?"PASS":"FAIL") << "]" << endl;
    CustomRunnableTestItem* cRunItem = new CustomRunnableTestItem();
    Report* tcRep = cRunItem->runItem(tcCtx);
    string tmp6 = *(tcRep->getSessionId());
    cout << "Test [" << ((tmp6.compare("MySessionId") == 0)?"PASS":"FAIL") << "]" << endl;
    CustomTearDownTestItem* ctdItem = new CustomTearDownTestItem();
    ctdItem->tearDownItem(tcCtx);

    delete sessionId;
    delete testPlanId;
    delete testId;
    delete obsId1;
    delete obsId2;
    delete report;
    delete aVar;
    delete bVar;
    delete ctxObj;
    delete myDescription;

	return 0;
}
