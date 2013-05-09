#include <support.h>
#include <observer.h>
#include <fake_observer.h>

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

    delete sessionId;
    delete testPlanId;
    delete testId;
    delete obsId1;
    delete obsId2;
    delete report;

	return 0;
}
