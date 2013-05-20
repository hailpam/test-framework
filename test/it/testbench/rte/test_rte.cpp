#include <unistd.h>

#include <thread.h>
#include <syncqueue.h>
#include <job.h>
#include <jobprod.h>
#include <jobcons.h>
#include <support.h>
#include <rte.h>

#include <observer.h>
#include <fake_observer.h>
#include <concrete_ctxobject.h>
#include <custom_testitems.h>
#include <testbench.h>
#include <concrete_testbuilder.h>


using namespace it::testbench::rte;
using namespace it::testbench::data;

int main(int argc, char* argv[])
{
    //-----------------------------------------------------------------------------------
    /// OBSERVER TEST
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ INIT SUPPORTING UNITs for TESTING PURPOSE                                    +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    string obsId1 = "Observer#1";
    string obsId2 = "Observer#2";
    FakeObserver* fakeObs1 = new FakeObserver();
    FakeObserver* fakeObs2 = new FakeObserver();

    /// CONCRETE CONTEXT OBJECT
    A* aVar1 = new A();
    B* bVar1 = new B();
    ConcreteContextObject* ctxObj1 = new ConcreteContextObject();
    string myDescription1 = "MyFavouriteDescription1";
    ctxObj1->setDescription(myDescription1);
    ctxObj1->setA(aVar1);
    ctxObj1->setB(bVar1);

    A* aVar2 = new A();
    B* bVar2 = new B();
    ConcreteContextObject* ctxObj2 = new ConcreteContextObject();
    string myDescription2 = "MyFavouriteDescription2";
    ctxObj2->setDescription(myDescription2);
    ctxObj2->setA(aVar2);
    ctxObj2->setB(bVar2);

    A* aVar3 = new A();
    B* bVar3 = new B();
    ConcreteContextObject* ctxObj3 = new ConcreteContextObject();
    string myDescription3 = "MyFavouriteDescription3";
    ctxObj3->setDescription(myDescription3);
    ctxObj3->setA(aVar3);
    ctxObj3->setB(bVar3);

    A* aVar4 = new A();
    B* bVar4 = new B();
    ConcreteContextObject* ctxObj4 = new ConcreteContextObject();
    string myDescription4 = "MyFavouriteDescription4";
    ctxObj4->setDescription(myDescription4);
    ctxObj4->setA(aVar4);
    ctxObj4->setB(bVar4);

    A* aVar5 = new A();
    B* bVar5 = new B();
    ConcreteContextObject* ctxObj5 = new ConcreteContextObject();
    string myDescription5 = "MyFavouriteDescription5";
    ctxObj5->setDescription(myDescription5);
    ctxObj5->setA(aVar5);
    ctxObj5->setB(bVar5);

    A* aVar6 = new A();
    B* bVar6 = new B();
    ConcreteContextObject* ctxObj6 = new ConcreteContextObject();
    string myDescription6 = "MyFavouriteDescription6";
    ctxObj6->setDescription(myDescription6);
    ctxObj6->setA(aVar6);
    ctxObj6->setB(bVar6);

    A* aVar7 = new A();
    B* bVar7 = new B();
    ConcreteContextObject* ctxObj7 = new ConcreteContextObject();
    string myDescription7 = "MyFavouriteDescription7";
    ctxObj7->setDescription(myDescription7);
    ctxObj7->setA(aVar7);
    ctxObj7->setB(bVar7);

    A* aVar8 = new A();
    B* bVar8 = new B();
    ConcreteContextObject* ctxObj8 = new ConcreteContextObject();
    string myDescription8 = "MyFavouriteDescription8";
    ctxObj8->setDescription(myDescription8);
    ctxObj8->setA(aVar8);
    ctxObj8->setB(bVar8);

    /// TEST ITEMs
    SetupTestItem* cSetItem1 = new CustomSetupItem();
    SetupTestItem* cSetItem2 = new CustomSetupItem();
    SetupTestItem* cSetItem3 = new CustomSetupItem();
    SetupTestItem* cSetItem4 = new CustomSetupItem();
    SetupTestItem* cSetItem5 = new CustomSetupItem();
    SetupTestItem* cSetItem6 = new CustomSetupItem();
    SetupTestItem* cSetItem7 = new CustomSetupItem();
    SetupTestItem* cSetItem8 = new CustomSetupItem();
//    TestCaseContext* tcCtx1 = cSetItem->setupItem();
//    TestCaseContext* tcCtx2 = cSetItem->setupItem();
//    TestCaseContext* tcCtx3 = cSetItem->setupItem();
//    TestCaseContext* tcCtx4 = cSetItem->setupItem();
//    TestCaseContext* tcCtx5 = cSetItem->setupItem();
//    TestCaseContext* tcCtx6 = cSetItem->setupItem();
//    TestCaseContext* tcCtx7 = cSetItem->setupItem();
//    TestCaseContext* tcCtx8 = cSetItem->setupItem();
    RunnableTestItem* cRunItem1 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem2 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem3 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem4 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem5 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem6 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem7 = new CustomRunnableTestItem();
    RunnableTestItem* cRunItem8 = new CustomRunnableTestItem();
    TearDownTestItem* ctdItem1 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem2 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem3 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem4 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem5 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem6 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem7 = new CustomTearDownTestItem();
    TearDownTestItem* ctdItem8 = new CustomTearDownTestItem();

    /// TEST CASEs
    TestCase* tCase1 = new TestCase();
    tCase1->setTestCaseNumber(1);
    tCase1->setSetupTestItem(cSetItem1);
    tCase1->setTearDownTestItem(ctdItem1);
    tCase1->addRunnableTestItem(cRunItem1);
    tCase1->setTestCaseContextObject(ctxObj1);
    //
    TestCase* tCase2 = new TestCase();
    tCase2->setTestCaseNumber(2);
    tCase2->setSetupTestItem(cSetItem2);
    tCase2->setTearDownTestItem(ctdItem2);
    tCase2->addRunnableTestItem(cRunItem2);
    tCase2->setTestCaseContextObject(ctxObj2);
    //
    TestCase* tCase3 = new TestCase();
    tCase3->setTestCaseNumber(3);
    tCase3->setSetupTestItem(cSetItem3);
    tCase3->setTearDownTestItem(ctdItem3);
    tCase3->addRunnableTestItem(cRunItem3);
    tCase3->setTestCaseContextObject(ctxObj3);
    //
    TestCase* tCase4 = new TestCase();
    tCase4->setTestCaseNumber(4);
    tCase4->setSetupTestItem(cSetItem4);
    tCase4->setTearDownTestItem(ctdItem4);
    tCase4->addRunnableTestItem(cRunItem4);
    tCase4->setTestCaseContextObject(ctxObj4);
    //
    TestCase* tCase5 = new TestCase();
    tCase5->setTestCaseNumber(5);
    tCase5->setSetupTestItem(cSetItem5);
    tCase5->setTearDownTestItem(ctdItem5);
    tCase5->addRunnableTestItem(cRunItem5);
    tCase5->setTestCaseContextObject(ctxObj5);
    //
    TestCase* tCase6 = new TestCase();
    tCase6->setTestCaseNumber(6);
    tCase6->setSetupTestItem(cSetItem6);
    tCase6->setTearDownTestItem(ctdItem6);
    tCase6->addRunnableTestItem(cRunItem6);
    tCase6->setTestCaseContextObject(ctxObj6);
    //
    TestCase* tCase7 = new TestCase();
    tCase7->setTestCaseNumber(7);
    tCase7->setSetupTestItem(cSetItem7);
    tCase7->setTearDownTestItem(ctdItem7);
    tCase7->addRunnableTestItem(cRunItem7);
    tCase7->setTestCaseContextObject(ctxObj7);
    //
    TestCase* tCase8 = new TestCase();
    tCase8->setTestCaseNumber(8);
    tCase8->setSetupTestItem(cSetItem8);
    tCase8->setTearDownTestItem(ctdItem8);
    tCase8->addRunnableTestItem(cRunItem8);
    tCase8->setTestCaseContextObject(ctxObj8);

    /// TEST PLAN
    TestPlan* tPlan = new TestPlan();
    tPlan->addTestCase(0, tCase1);
    tPlan->addTestCase(1, tCase2);
    tPlan->addTestCase(2, tCase3);
    tPlan->addTestCase(3, tCase4);
    tPlan->addTestCase(4, tCase5);
    tPlan->addTestCase(5, tCase6);
    tPlan->addTestCase(6, tCase7);
    tPlan->addTestCase(7, tCase8);
    string tPlanId = "My Test Plan";
    tPlan->setTestPlanId(tPlanId);

    /// TESTBENCH CONFIGURATION
    TestBenchConfiguration* tbCfg = new TestBenchConfiguration();
    string sId = "TBCFG_SessionId";
    tbCfg->setSessionId(sId);
    Range tbR;
    tbR.from = 0;
    tbR.to = 3;
    tbCfg->addRange(tPlanId, tbR);
    tbCfg->addTestPlan(&tPlanId, tPlan);
    tbCfg->setNrOfThreads(1);
    //-----------------------------------------------------------------------------------

    /**
     * JOB TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ JOB TEST                                                                     +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    Job* j = new Job();
    TestCase* tCase0 = NULL;
    ReturnCode* outcome = j->setTestCase(tCase0);
    TEST_EQ(1,"Job Testing","j->setTestCase(tCase) - expected an error: NULL pointer provided","Reporting ERROR", outcome->code, ERROR);
    delete outcome;
    outcome = j->setTestCase(tCase1);
    TEST_EQ(2,"Job Testing","j->setTestCase(tCase) - expected a correct initialization","Reporting SUCCESS", outcome->code, SUCCESS);
    delete outcome;
    #warning TODO cross-check NULL pointer for TestCase in case no TestItem is defined
    outcome = j->executeTestCase();
    TEST_EQ(3,"Job Testing","j->executeTestCase()","OK, items correctly defined: execution successful", outcome->code, SUCCESS);
    Report* report;
    delete outcome;
    outcome = j->generateReport(report);
    TEST_EQ(4,"Job Testing","j->generateReport(report)","OK, report successfully generated", outcome->code, SUCCESS);
    delete outcome;
    delete tCase0;
    delete j;

    /**
     * SYNCHRONIZED QUEUE TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ SYNCHRONIZED QUEUE TEST: basic, no concurrency                               +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    SynchronizedQueue<Job*> queue;
    queue.enqueue(j);
    Job* j1 = queue.dequeue();
    TEST_EQ(1,"Job Testing","Job* j1 = queue.dequeue(); - expected the same pointer","Same pointer should be found", j, j1);

    /**
     * THREAD WRAPPER TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ THREAD TEST                                                                  +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    bool testJobConsumer = true;
    bool testJobProducer = true;
    bool moreTCThanThreads = true;
    bool moreThreadsThanTC = false;
    bool inhibitTCReload = false;
    unsigned int nrOfLoads = 1;
    /// QUEUEs
    SynchronizedQueue<Job*>* sharedQueue = new SynchronizedQueue<Job*>();       //Job Queue
    string jQueueLabel = "Shared Job Queue";
    sharedQueue->setLabel(jQueueLabel);
    list<TestCase*>* listOfTC = new list<TestCase*>();                          //list of Test Cases
    listOfTC->push_back(tCase1);
    listOfTC->push_back(tCase2);
    listOfTC->push_back(tCase3);
    listOfTC->push_back(tCase4);
    if(moreTCThanThreads) {
        listOfTC->push_back(tCase5);
        listOfTC->push_back(tCase6);
        listOfTC->push_back(tCase7);
        listOfTC->push_back(tCase8);
    }
    SynchronizedQueue<Report*>* reportQueue = new SynchronizedQueue<Report*>();   //Report Queue
    string rQueueLabel = "Shared Report Queue";
    reportQueue->setLabel(rQueueLabel);
    ReturnCode* retCode;
    JobConsumer* jConsumer1;
    JobConsumer* jConsumer2;
    JobConsumer* jConsumer3;
    JobConsumer* jConsumer4;
    JobConsumer* jConsumer5;
    JobConsumer* jConsumer6;
    JobConsumer* jConsumer7;
    JobConsumer* jConsumer8;
    JobProducer* jProducer;
    /// JOB CONSUMER
    if(testJobConsumer) {
        jConsumer1 = new JobConsumer();
        jConsumer2 = new JobConsumer();
        jConsumer3 = new JobConsumer();
        jConsumer4 = new JobConsumer();
        if(moreThreadsThanTC) {
            jConsumer5 = new JobConsumer();
            jConsumer6 = new JobConsumer();
            jConsumer7 = new JobConsumer();
            jConsumer8 = new JobConsumer();
        }
        string tId1 = "Thread Job Consumer #1";
        string tId2 = "Thread Job Consumer #2";
        string tId3 = "Thread Job Consumer #3";
        string tId4 = "Thread Job Consumer #4";
        string tId5 = "Thread Job Consumer #5";
        string tId6 = "Thread Job Consumer #6";
        string tId7 = "Thread Job Consumer #7";
        string tId8 = "Thread Job Consumer #8";
        jConsumer1->setThreadId(tId1);
        jConsumer2->setThreadId(tId2);
        jConsumer3->setThreadId(tId3);
        jConsumer4->setThreadId(tId4);
        if(moreThreadsThanTC) {
            jConsumer5->setThreadId(tId5);
            jConsumer6->setThreadId(tId6);
            jConsumer7->setThreadId(tId7);
            jConsumer8->setThreadId(tId8);
        }
        DATA_INFO_VAL("Tread Identifier", *jConsumer1->getThreadId());
        DATA_INFO_VAL("Tread Identifier", *jConsumer2->getThreadId());
        DATA_INFO_VAL("Tread Identifier", *jConsumer3->getThreadId());
        DATA_INFO_VAL("Tread Identifier", *jConsumer4->getThreadId());
        if(moreThreadsThanTC) {
            DATA_INFO_VAL("Tread Identifier", *jConsumer5->getThreadId());
            DATA_INFO_VAL("Tread Identifier", *jConsumer6->getThreadId());
            DATA_INFO_VAL("Tread Identifier", *jConsumer7->getThreadId());
            DATA_INFO_VAL("Tread Identifier", *jConsumer8->getThreadId());
        }
        retCode = const_cast<ReturnCode*>(jConsumer1->setJobSharedQueue(sharedQueue));
        retCode = const_cast<ReturnCode*>(jConsumer2->setJobSharedQueue(sharedQueue));
        retCode = const_cast<ReturnCode*>(jConsumer3->setJobSharedQueue(sharedQueue));
        retCode = const_cast<ReturnCode*>(jConsumer4->setJobSharedQueue(sharedQueue));
        if(moreThreadsThanTC) {
            retCode = const_cast<ReturnCode*>(jConsumer5->setJobSharedQueue(sharedQueue));
            retCode = const_cast<ReturnCode*>(jConsumer6->setJobSharedQueue(sharedQueue));
            retCode = const_cast<ReturnCode*>(jConsumer7->setJobSharedQueue(sharedQueue));
            retCode = const_cast<ReturnCode*>(jConsumer8->setJobSharedQueue(sharedQueue));
        }
        TEST_EQ(1,"Job Consumer","retCode = jConsumer->setJobSharedQueue(sharedQueue); - expected success","Successfull Job Shared Queue Inizialization", retCode->code, SUCCESS);
        delete retCode;
        retCode = const_cast<ReturnCode*>(jConsumer1->setReportSharedQueue(reportQueue));
        retCode = const_cast<ReturnCode*>(jConsumer2->setReportSharedQueue(reportQueue));
        retCode = const_cast<ReturnCode*>(jConsumer3->setReportSharedQueue(reportQueue));
        retCode = const_cast<ReturnCode*>(jConsumer4->setReportSharedQueue(reportQueue));
        if(moreThreadsThanTC) {
            retCode = const_cast<ReturnCode*>(jConsumer5->setReportSharedQueue(reportQueue));
            retCode = const_cast<ReturnCode*>(jConsumer6->setReportSharedQueue(reportQueue));
            retCode = const_cast<ReturnCode*>(jConsumer7->setReportSharedQueue(reportQueue));
            retCode = const_cast<ReturnCode*>(jConsumer8->setReportSharedQueue(reportQueue));
        }
        TEST_EQ(2,"Job Consumer","retCode = jConsumer->setReportSharedQueue(reportQueue); - expected success","Successfull Repor Shared Queue Inizialization", retCode->code, SUCCESS);
        delete retCode;
        jConsumer1->start(); //expected to wait until the 1st job is available on the queue
        jConsumer2->start(); //expected to wait until the 1st job is available on the queue
        jConsumer3->start(); //expected to wait until the 1st job is available on the queue
        jConsumer4->start(); //expected to wait until the 1st job is available on the queue
        if(moreThreadsThanTC) {
            jConsumer5->start(); //expected to wait until the 1st job is available on the queue
            jConsumer6->start(); //expected to wait until the 1st job is available on the queue
            jConsumer7->start(); //expected to wait until the 1st job is available on the queue
            jConsumer8->start(); //expected to wait until the 1st job is available on the queue
        }
        sleep(4);
    }
    //
    if(testJobProducer) {
        /// JOB PRODUCER
        jProducer = new JobProducer();
        DATA_INFO_VAL("Tread Identifier", *jProducer->getThreadId());
        retCode = const_cast<ReturnCode*>(jProducer->setJobSharedQueue(sharedQueue));
        TEST_EQ(3,"Job Producer","retCode = jProducer->setJobSharedQueue(sharedQueue); - expected success","Successfull Shared Queue Inizialization", retCode->code, SUCCESS);
        delete retCode;
//        retCode = const_cast<ReturnCode*>(jProducer->loadTestCases(listOfTC));
//        TEST_EQ(4,"Job Producer","jProducer->loadTestCases(listOfTC) - expected success","Successfull List of Test Cases Initialization", retCode->code, SUCCESS);
//        delete retCode;
        jProducer->start();
        sleep(1);
//        jProducer->pause();
        DATA_INFO("Going to sleep for 2 seconds...");
        sleep(2);
        DATA_INFO("... back from sleep!");
        if(!inhibitTCReload) {
            for(int idx = 0; idx < nrOfLoads; idx++) {
                //load new Test Cases
                listOfTC = new list<TestCase*>();                          //list of Test Cases
                listOfTC->push_back(tCase1);
                listOfTC->push_back(tCase2);
                listOfTC->push_back(tCase3);
                listOfTC->push_back(tCase4);
                if(moreTCThanThreads) {
                    listOfTC->push_back(tCase1);
                    listOfTC->push_back(tCase2);
                    listOfTC->push_back(tCase3);
                    listOfTC->push_back(tCase4);
                }
                DATA_INFO_VAL("Publishing Test Case Set #", (idx +1));
                retCode = const_cast<ReturnCode*>(jProducer->loadTestCases(listOfTC));
                TEST_EQ(5,"Job Producer","retCode = jProducer->loadTestCases(listOfTC)); - expected success","Successfull List of Test Cases Initialization", retCode->code, SUCCESS);
    //            jProducer->resume();
                sleep(2);
            }
        }
        DATA_INFO("Going to sleep for 1 seconds...");
        sleep(1);
        DATA_INFO("... back from sleep!");
    }
    /// THREADs killing
    if(testJobConsumer) {
        jConsumer1->killIt();
        jConsumer2->killIt();
        jConsumer3->killIt();
        jConsumer4->killIt();
        if(moreThreadsThanTC) {
            jConsumer5->killIt();
            jConsumer6->killIt();
            jConsumer7->killIt();
            jConsumer8->killIt();
        }
//        Job* fakeJob = new Job();
//        sharedQueue->enqueue(fakeJob);
//        sharedQueue->enqueue(fakeJob);
//        sharedQueue->enqueue(fakeJob);
//        sharedQueue->enqueue(fakeJob);
//        if(moreThreadsThanTC) {
//            sharedQueue->enqueue(fakeJob);
//            sharedQueue->enqueue(fakeJob);
//            sharedQueue->enqueue(fakeJob);
//            sharedQueue->enqueue(fakeJob);
//        }
    }
    if(testJobProducer)
        jProducer->killIt();
    /// THREADs JOIN
    if(testJobProducer)
        jProducer->join();
    if(testJobConsumer) {
        jConsumer1->join();
        jConsumer2->join();
        jConsumer3->join();
        jConsumer4->join();
        if(moreThreadsThanTC) {
            jConsumer5->join();
            jConsumer6->join();
            jConsumer7->join();
            jConsumer8->join();
        }
    }

    /**
     * RTE TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ RTE TEST                                                                     +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    bool testRTE = false;
    bool testInitEngine = false;
    if(testRTE) {
        RuntimeEngine* rte = new RuntimeEngine();
        retCode = rte->initEngine(0);
        TEST_EQ(1,"RTE Testing","rte->initEngine(0) - expected an error","Error, 0 is not a valid size", retCode->code, ERROR);
        delete retCode;
        retCode = rte->initEngine(257);
        TEST_EQ(2,"RTE Testing","rte->initEngine(257) - expected an error","Error, 0 is not a valid size", retCode->code, ERROR);
        delete retCode;
        if(testInitEngine) {
            retCode = rte->initEngine(1);
            TEST_EQ(3,"RTE Testing","rte->initEngine(5) ","Ok, 5 is in the range", retCode->code, SUCCESS);
            delete retCode;
            sleep(10);
        }
        TestBenchConfiguration* fakePtr = NULL;
        retCode = rte->launchTestPlan(fakePtr, tPlanId);
        TEST_EQ(4,"RTE Testing","rte->launchTestPlan(fakePtr, tPlanId) - expected an error","Error, NULL Pointer in Input", retCode->code, ERROR);
        delete retCode;
        try{
            retCode = rte->launchTestPlan(tbCfg, tPlanId);
            TEST_EQ(5,"RTE Testing","rte->launchTestPlan(tbCfg, tPlanId)","OK, test cases should be retrieved and loaded to JobProducer", retCode->code, SUCCESS);
            delete retCode;
        }catch(TestFrameworkException& exception) {
            TEST_EQ(5,"RTE Testing","rte->launchTestPlan(tbCfg, tPlanId) - unexpected error","Error, unexpected in launching a Test Plan", 1, -1);
            DATA_ERR_VAL("Error message ", string(exception.what()));
         }
        //
        rte->addObserver(fakeObs1);
        rte->addObserver(fakeObs2);
        unsigned int nrOfObs = rte->actualNrOfObservers();
        TEST_EQ(6,"RTE Testing","nrOfObs = rte->actualNrOfObservers()","OK, expected a number of Observers equal to the ones registered", nrOfObs, 2);
    }

    /// DELETE
    if(testJobProducer)
        delete jProducer;
    if(testJobConsumer) {
        delete jConsumer1;
        delete jConsumer2;
        delete jConsumer3;
        delete jConsumer4;
        if(moreThreadsThanTC) {
            delete jConsumer5;
            delete jConsumer6;
            delete jConsumer7;
            delete jConsumer8;
        }
    }
    delete listOfTC;
    delete sharedQueue;
    delete tbCfg;

	return 0;
}
