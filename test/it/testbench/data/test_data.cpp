#include <support.h>
#include <observer.h>
#include <fake_observer.h>
#include <concrete_ctxobject.h>
#include <custom_testitems.h>
#include <testbench.h>
#include <concrete_testbuilder.h>

#include <iostream>


using namespace std;

using namespace it::testbench::data;

int main(int argc, char* argv[])
{
    /// REPORT TEST
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ REPORT TEST                                                                  +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    Report* report = new Report();
    string* sessionId = new string("MySessionId");
    report->setSessionId(sessionId);
    TEST_EQ(1,"Report","tcLoader->setSessionId()","Check Session Id",(sessionId->compare(*(report->getSessionId()))),0);
    //
    string* testPlanId = new string("MyTestPlanId");
    report->setTestPlanId(testPlanId);
    TEST_EQ(2,"Report","tcLoader->setTestPlanId()","Load all Test Cases",(testPlanId->compare(*(report->getTestPlanId()))),0);
    //
    string* testId = new string("MyTestId");
    report->setTestId(testId);
    TEST_EQ(3,"Report","tcLoader->setTestId()","Load all Test Cases",(testId->compare(*(report->getTestId()))),0);
    //
    FormattedResource res;
    res.ext = "TEXT";
    res.content = "aahahahahhahahahahaah";
    res.name = "blah";
    res.hash = "";
    report->setFormattedResorce(&res);
    TEST_EQ(4,"Report","tcLoader->setFormattedResorce()","Check Content",(res.content.compare(report->getFormattedResource()->content)),0);
    TEST_EQ(5,"Report","tcLoader->setFormattedResorce()","Check Ext",(res.ext.compare(report->getFormattedResource()->ext)),0);
    TEST_EQ(6,"Report","tcLoader->setFormattedResorce()","Check Hash",(res.hash.compare(report->getFormattedResource()->hash)),0);
    TEST_EQ(7,"Report","tcLoader->setFormattedResorce()","Check Name",(res.name.compare(report->getFormattedResource()->name)),0);

    /// OBSERVER TEST
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ OBESERVER TEST                                                               +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    string* obsId1 = new string("Observer#1");
    string* obsId2 = new string("Observer#2");
    FakeObserver* fakeObs1 = new FakeObserver();
    FakeObserver* fakeObs2 = new FakeObserver();
    fakeObs1->setWhoAmI(obsId1);
    fakeObs2->setWhoAmI(obsId2);
    cout << "[OBSERVER TEST] Test [" << ((obsId1->compare(*(fakeObs1->getWhoAmI())) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "[OBSERVER TEST] Test [" << ((obsId2->compare(*(fakeObs2->getWhoAmI())) == 0)?"PASS":"FAIL") << "]" << endl;
    /// SUBJECT TEST
    Subject* aSubject = new Subject();
    aSubject->addObserver(fakeObs1);
    aSubject->addObserver(fakeObs2);
    aSubject->notifyObservers(report);

    /// CONCRETE CONTEXT OBJECT
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ CONCRETE CONTEXT OBJECT                                                      +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    A* aVar = new A();
    B* bVar = new B();
    ConcreteContextObject* ctxObj = new ConcreteContextObject();
    string* myDescription = new string("MyFavouriteDescription");
    ctxObj->setDescription(myDescription);
    cout << "[CONCRETE CONTEXT OBJECT ]Test [" << ((ctxObj->getDescription()->compare(*myDescription) == 0)?"PASS":"FAIL") << "]" << endl;
    ctxObj->setA(aVar);
    ctxObj->setB(bVar);
    string tmp1 = aVar->getAString();
    string tmp2 = bVar->getBString();
    string tmp3 = ctxObj->getA()->getAString();
    string tmp4 = ctxObj->getB()->getBString();
    cout << "[CONCRETE CONTEXT OBJECT] Test [" << ((tmp1.compare(tmp3) == 0)?"PASS":"FAIL") << "]" << endl;
    cout << "[CONCRETE CONTEXT OBJECT] Test [" << ((tmp2.compare(tmp4) == 0)?"PASS":"FAIL") << "]" << endl;

    /// TEST ITEMs
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ TEST ITEMSs                                                                  +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    SetupTestItem* cSetItem = new CustomSetupItem();
    TestCaseContext* tcCtx = cSetItem->setupItem();
    string tmp5 = *(tcCtx->getDescription());
    cout << "[TEST ITEMs] Test [" << ((tmp5.compare("MyFavouriteDescription") == 0)?"PASS":"FAIL") << "]" << endl;
    RunnableTestItem* cRunItem = new CustomRunnableTestItem();
    Report* tcRep = cRunItem->runItem(tcCtx);
    string tmp6 = *(tcRep->getSessionId());
    cout << "[TEST ITEMs] Test [" << ((tmp6.compare("MySessionId") == 0)?"PASS":"FAIL") << "]" << endl;
    TearDownTestItem* ctdItem = new CustomTearDownTestItem();
    ctdItem->tearDownItem(tcCtx);

    /// TEST CASE
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ TEST CASE                                                                    +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    TestCase* tCase = new TestCase();
    tCase->setTestCaseNumber(1);
    tCase->setSetupTestItem(cSetItem);
    tCase->setTearDownTestItem(ctdItem);
    tCase->addRunnableTestItem(cRunItem);
    bool bSetup = tCase->setupTestCase();
    cout << "[TEST CASE] Test [" << (bSetup?"PASS":"FAIL") << "]" << endl;
    bool rTC = tCase->runTestCase();
    cout << "[TEST CASE] Test [" << (rTC?"PASS":"FAIL") << "]" << endl;
    bool tdTC = tCase->tearDownTestCase();
    cout << "[TEST CASE] Test [" << (tdTC?"PASS":"FAIL") << "]" << endl;

    /// TEST PLAN
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ TEST PLAN                                                                    +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    TestPlan* tPlan = new TestPlan();
    tPlan->addTestCase(0, tCase);
    tPlan->addTestCase(1, tCase);
    TestCase* tmpCase = const_cast<TestCase*>(tPlan->retrieveTestCase(1));
    cout << "[TEST CASE] Test [" << ((tmpCase->getTestCaseNumber() == 1)?"PASS":"FAIL") << "]" << endl;
    tmpCase->setTestCaseNumber(10);
    bool uTP = tPlan->updateTestCase(1, tmpCase);
    tmpCase = const_cast<TestCase*>(tPlan->retrieveTestCase(1));
    cout << "[TEST CASE] Test [" << (uTP && (tmpCase->getTestCaseNumber() == 10)?"PASS":"FAIL") << "]" << endl;
    tPlan->addTestCase(2, tmpCase);
    int tcNo = tPlan->getNrOfTestCases();
    tPlan->removeTestCase(2);
    int tcNo1 = tPlan->getNrOfTestCases();
    cout << "[TEST CASE] Test [" << (tcNo1 == (tcNo - 1)?"PASS":"FAIL") << "]" << endl;

    /// TESTBENCH CONFIGURATION
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ TESTBENCH CONFIGURATION                                                      +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    TestBenchConfiguration* tbCfg = new TestBenchConfiguration();
    string sId = "TBCFG_SessionId";
    tbCfg->setSessionId(&sId);
    string* tmpSId = const_cast<string*>(tbCfg->getSessionId());
    cout << "[TESTBENCH CONFIGURATION] Test [" << (sId.compare(*tmpSId) == 0?"PASS":"FAIL") << "]" << endl;
    sId = "MyTestPlan";
    Range tbR;
    tbR.from = 0;
    tbR.to = 2;
    tbCfg->addRange(&sId, &tbR);
    Range* tbRTemp = const_cast<Range*>(tbCfg->retrieveRange(&sId));
    cout << "[TESTBENCH CONFIGURATION] Test [" << ((tbRTemp->from == tbR.from && tbRTemp->to == tbR.to)?"PASS":"FAIL") << "]" << endl;
    tbCfg->addTestPlan(&sId, tPlan);
    int orTPNo = tPlan->getNrOfTestCases();
    TestPlan* retTP = const_cast<TestPlan*>(tbCfg->retrieveTestPlan(&sId));
    cout << "[TESTBENCH CONFIGURATION] Test [" << ((retTP->getNrOfTestCases() == orTPNo)?"PASS":"FAIL") << "]" << endl;

    /// TEST CASE LOADER
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ TEST CASE LOADER                                                             +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    TestCaseLoader* tcLoader = new TestCaseLoader();
    bool bTCLoad = tcLoader->loadAllTestCases();
    TEST_EQ(1,"Test Case Loader - No Builders","tcLoader->loadAllTestCases()","Load all Test Cases",bTCLoad,1);

    bTCLoad = tcLoader->loadTestCase(1);
    TEST_EQ(2,"Test Case Loader - No Builders","tcLoader->loadTestCase(1)","Load Test Case #1",bTCLoad,1);

    TestCase* retTC = const_cast<TestCase*>(tcLoader->getLoadedTestCase(1));
    TEST_EQ(3,"Test Case Loader - No Builders","tcLoader->getLoadedTestCase(1)","Get Test Case Number #1",retTC,0);

    vector<TestCase*>* retVectTC = const_cast<vector<TestCase*>*>(tcLoader->getAllLoadedTestCases());
    TEST_NEQ(4,"Test Case Loader - No Builders","tcLoader->getAllLoadedTestCases()","Get all Test Cases",retVectTC,0);
    TEST_EQ(5,"Test Case Loader - No Builders","tcLoader->getAllLoadedTestCases()->size()","Loaded Test Case Vector Size",retVectTC->size(),0);

    /// CONCRETE TEST BUILDER
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ CONCRETE TEST BUILDING                                                       +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    TestCaseBuilder1* ctb1 = new TestCaseBuilder1();
    TestCaseBuilder2* ctb2 = new TestCaseBuilder2();
    TestCaseBuilder3* ctb3 = new TestCaseBuilder3();

    TestCase* tcBuilt1 = ctb1->buildTestCase();
    TEST_EQ(6,"Test Case Loader","tcBuilt1->getTestCaseNumber()","Get Test Case Number",tcBuilt1->getTestCaseNumber(),1);

    TestCase* tcBuilt2 = ctb2->buildTestCase();
    TEST_EQ(7,"Test Case Loader","tcBuilt2->getTestCaseNumber()","Get Test Case Number",tcBuilt2->getTestCaseNumber(),2);

    TestCase* tcBuilt3 = ctb3->buildTestCase();
    TEST_EQ(8,"Test Case Loader","tcBuilt3->getTestCaseNumber()","Get Test Case Number",tcBuilt3->getTestCaseNumber(),3);


    bool regTCBuild = tcLoader->registerTestCaseBuilder(0, ctb1);
    TEST_EQ(9,"Test Case Loader","tcLoader->registerTestCaseBuilder(0, ctb1)","Regist 1st Builder",regTCBuild,1);

    regTCBuild = tcLoader->registerTestCaseBuilder(1, ctb2);
    TEST_EQ(10,"Test Case Loader","tcLoader->registerTestCaseBuilder(1, ctb2)","Regist 2st Builder",regTCBuild,1);

    regTCBuild = tcLoader->registerTestCaseBuilder(2, ctb3);
    TEST_EQ(11,"Test Case Loader","tcLoader->registerTestCaseBuilder(2, ctb3)","Regist 2st Builder",regTCBuild,1);

    bTCLoad = tcLoader->loadTestCase(1);
    cout << regTCBuild;
    TEST_EQ(12,"Test Case Loader","tcLoader->loadTestCase(1)","Load 1st Test Case",regTCBuild,1);

    TestCase* loadTC = const_cast<TestCase*>(tcLoader->getLoadedTestCase(1));
    TEST_NEQ(13,"Test Case Loader","tcLoader->getLoadedTestCase(1)","Get 1st Test Case",loadTC,0);
    TEST_EQ(14,"Test Case Loader","tcLoader->getLoadedTestCase(1)","1st Test Case ID",loadTC->getTestCaseNumber(),(1+1));

    bTCLoad = tcLoader->loadAllTestCases();
    TEST_EQ(15,"Test Case Loader","tcLoader->loadAllTestCases()","Load all Test Cases Registered",regTCBuild,1);

    TestCase* loadTC0 = const_cast<TestCase*>(tcLoader->getLoadedTestCase(0+1));
    TEST_NEQ(16,"Test Case Loader","tcLoader->getLoadedTestCase(0)","Get 1st Test Case",loadTC0,0);
    TEST_EQ(17,"Test Case Loader","tcLoader->getLoadedTestCase(0)","1st Test Case ID",loadTC0->getTestCaseNumber(),(0+1));
    cout << "testCase0::"<<loadTC0->getTestCaseNumber()<< endl;

    TestCase* loadTC1 = const_cast<TestCase*>(tcLoader->getLoadedTestCase(1+1));
    TEST_NEQ(18,"Test Case Loader","tcLoader->getLoadedTestCase(1)","Get 1st Test Case",loadTC1,0);
    TEST_EQ(19,"Test Case Loader","tcLoader->getLoadedTestCase(1)","1st Test Case ID",loadTC1->getTestCaseNumber(),(1+1));
    cout << "testCase1::"<<loadTC1->getTestCaseNumber()<< endl;

    TestCase* loadTC2 = const_cast<TestCase*>(tcLoader->getLoadedTestCase(2+1));
    TEST_NEQ(20,"Test Case Loader","tcLoader->getLoadedTestCase(2)","Get 1st Test Case",loadTC2,0);
    TEST_EQ(21,"Test Case Loader","tcLoader->getLoadedTestCase(2)","1st Test Case ID",loadTC2->getTestCaseNumber(),(2+1));
    cout << "testCase2::"<<loadTC2->getTestCaseNumber()<< endl;


    //delete tCase;
    //delete tPlan;
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
