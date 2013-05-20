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
    /**
     * JOB TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ JOB TEST                                                                     +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    Job* j = new Job();
    TestCase* tCase0 = NULL;
    ReturnCode* outcome = j->setTestCase(tCase0);
    delete outcome;
    TEST_EQ(1,"Job Testing","j->setTestCase(tCase) - expected an error: NULL pointer provided","Reporting ERROR", outcome->code, ERROR);
    tCase0 = new TestCase();
    outcome = j->setTestCase(tCase0);
    delete outcome;
    TEST_EQ(2,"Job Testing","j->setTestCase(tCase) - expected a correct initialization","Reporting SUCCESS", outcome->code, SUCCESS);
    #warning TODO cross-check NULL pointer for TestCase in case no TestItem is defined
//    outcome = j->executeTestCase();
//    TEST_EQ(3,"Job Testing","j->executeTestCase() - expected an error - no TestItems defined for the TestCase","Reporting ERROR", outcome->code, ERROR);
    Report* report;
    outcome = j->generateReport(report);
    delete outcome;
    TEST_EQ(4,"Job Testing","j->generateReport(report) - expected an error - TestCase not executed","Reporting ERROR", outcome->code, ERROR);
    delete tCase0;

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
    A* aVar = new A();
    B* bVar = new B();
    ConcreteContextObject* ctxObj = new ConcreteContextObject();
    string myDescription = "MyFavouriteDescription";
    ctxObj->setDescription(myDescription);
    ctxObj->setA(aVar);
    ctxObj->setB(bVar);

    /// TEST ITEMs
    SetupTestItem* cSetItem = new CustomSetupItem();
    TestCaseContext* tcCtx = cSetItem->setupItem();
    RunnableTestItem* cRunItem = new CustomRunnableTestItem();
    TearDownTestItem* ctdItem = new CustomTearDownTestItem();

    /// TEST CASEs
    TestCase* tCase1 = new TestCase();
    tCase1->setTestCaseNumber(1);
    tCase1->setSetupTestItem(cSetItem);
    tCase1->setTearDownTestItem(ctdItem);
    tCase1->addRunnableTestItem(cRunItem);
    tCase1->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase2 = new TestCase();
    tCase2->setTestCaseNumber(2);
    tCase2->setSetupTestItem(cSetItem);
    tCase2->setTearDownTestItem(ctdItem);
    tCase2->addRunnableTestItem(cRunItem);
    tCase2->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase3 = new TestCase();
    tCase3->setTestCaseNumber(3);
    tCase3->setSetupTestItem(cSetItem);
    tCase3->setTearDownTestItem(ctdItem);
    tCase3->addRunnableTestItem(cRunItem);
    tCase3->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase4 = new TestCase();
    tCase4->setTestCaseNumber(4);
    tCase4->setSetupTestItem(cSetItem);
    tCase4->setTearDownTestItem(ctdItem);
    tCase4->addRunnableTestItem(cRunItem);
    tCase4->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase5 = new TestCase();
    tCase5->setTestCaseNumber(5);
    tCase5->setSetupTestItem(cSetItem);
    tCase5->setTearDownTestItem(ctdItem);
    tCase5->addRunnableTestItem(cRunItem);
    tCase5->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase6 = new TestCase();
    tCase6->setTestCaseNumber(6);
    tCase6->setSetupTestItem(cSetItem);
    tCase6->setTearDownTestItem(ctdItem);
    tCase6->addRunnableTestItem(cRunItem);
    tCase6->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase7 = new TestCase();
    tCase7->setTestCaseNumber(7);
    tCase7->setSetupTestItem(cSetItem);
    tCase7->setTearDownTestItem(ctdItem);
    tCase7->addRunnableTestItem(cRunItem);
    tCase7->setTestCaseContextObject(ctxObj);
    //
    TestCase* tCase8 = new TestCase();
    tCase8->setTestCaseNumber(8);
    tCase8->setSetupTestItem(cSetItem);
    tCase8->setTearDownTestItem(ctdItem);
    tCase8->addRunnableTestItem(cRunItem);
    tCase8->setTestCaseContextObject(ctxObj);

    /// TEST PLAN
    TestPlan* tPlan = new TestPlan();
    tPlan->addTestCase(0, tCase1);
    tPlan->addTestCase(1, tCase2);
    tPlan->addTestCase(2, tCase3);
    tPlan->addTestCase(3, tCase4);
    tPlan->addTestCase(4, tCase5);
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
     * THREAD WRAPPER TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ THREAD TEST                                                                  +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    bool testJobConsumer = true;
    bool testJobProducer = true;
    bool moreTCThanThreads = true;
    bool moreThreadsThanTC = true;
    bool inhibitTCReload = true;
    /// QUEUEs
    SynchronizedQueue<Job*>* sharedQueue = new SynchronizedQueue<Job*>();       //Job Queue
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
        retCode = const_cast<ReturnCode*>(jProducer->loadTestCases(listOfTC));
        TEST_EQ(4,"Job Producer","jProducer->loadTestCases(listOfTC) - expected success","Successfull List of Test Cases Initialization", retCode->code, SUCCESS);
        delete retCode;
        jProducer->start();
        sleep(1);
//        jProducer->pause();
        DATA_INFO("Going to sleep for 20 seconds...");
        sleep(20);
        DATA_INFO("... back from sleep!");
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
        if(!inhibitTCReload) {
            retCode = const_cast<ReturnCode*>(jProducer->loadTestCases(listOfTC));
            TEST_EQ(5,"Job Producer","retCode = jProducer->loadTestCases(listOfTC)); - expected success","Successfull List of Test Cases Initialization", retCode->code, SUCCESS);
            jProducer->resume();
        }
        DATA_INFO("Going to sleep for 10 seconds...");
        sleep(10);
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
        Job* fakeJob = new Job();
        sharedQueue->enqueue(fakeJob);
        sharedQueue->enqueue(fakeJob);
        sharedQueue->enqueue(fakeJob);
        sharedQueue->enqueue(fakeJob);
        if(moreThreadsThanTC) {
            sharedQueue->enqueue(fakeJob);
            sharedQueue->enqueue(fakeJob);
            sharedQueue->enqueue(fakeJob);
            sharedQueue->enqueue(fakeJob);
        }
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
    bool testRTE = true;
    bool testInitEngine = true;
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
