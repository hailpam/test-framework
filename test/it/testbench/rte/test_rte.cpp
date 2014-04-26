#include <unistd.h>

#include <thread.h>
#include <syncqueue.h>
#include <job.h>
#include <jobprod.h>
#include <jobcons.h>
#include <support.h>
#include <rte.h>
#include <formatter_util.h>

#include <observer.h>
#include <fake_observer.h>
#include <concrete_ctxobject.h>
#include <custom_testitems.h>
#include <testbench.h>
#include <concrete_testbuilder.h>


using namespace it::testbench::rte;
using namespace it::testbench::data;
using namespace it::testbench::formatter;

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
    int nrOfTestCases = 400;
    //
    ConcreteContextObject* ctxObj = new ConcreteContextObject[nrOfTestCases];
    SetupTestItem* cSetItem = new CustomSetupItem[nrOfTestCases];
    RunnableTestItem* cRunItem = new CustomRunnableTestItem[nrOfTestCases];
    TearDownTestItem* ctdItem = new CustomTearDownTestItem[nrOfTestCases];
    TestCase* tCase = new TestCase[nrOfTestCases];
    //
    A* aVar = new A[nrOfTestCases];
    B* bVar = new B[nrOfTestCases];
    //
    for(int i = 0; i < nrOfTestCases; i++) {
        //
        string myDescription = "MyFavouriteDescription - [";
        myDescription += intToStr(i);
        myDescription += "]";
        //
        ctxObj->setDescription(myDescription);
        ctxObj->setA(&aVar[i]);
        ctxObj->setB(&bVar[i]);
        /// TEST CASEs
        tCase[i].setTestCaseNumber(i);
        tCase[i].setSetupTestItem(&cSetItem[i]);
        tCase[i].setTearDownTestItem(&ctdItem[i]);
        tCase[i].addRunnableTestItem(&cRunItem[i]);
        tCase[i].setTestCaseContextObject(&ctxObj[i]);
    }

    /// TEST PLAN
    TestPlan* tPlan = new TestPlan();
    for(int j = 0; j < nrOfTestCases; j++) {
        tPlan->addTestCase(j, &tCase[j]);
    }
    //
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
    outcome = j->setTestCase(&tCase[0]);
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
    int nrOfThreadConsumer = 200;
    /// QUEUEs
    SynchronizedQueue<Job*>* sharedQueue = new SynchronizedQueue<Job*>();       //Job Queue
    string jQueueLabel = "Shared JOB Queue";
    sharedQueue->setLabel(jQueueLabel);
    SynchronizedQueue<Report*>* reportQueue = new SynchronizedQueue<Report*>();   //Report Queue
    string rQueueLabel = "Shared REPORT Queue";
    reportQueue->setLabel(rQueueLabel);
    //
    ReturnCode* retCode;
    /// JOB CONSUMER
    JobConsumer* jConsumer = new JobConsumer[nrOfThreadConsumer];
    for(int z = 0; z < nrOfThreadConsumer; z++) {
//        jConsumer = new JobConsumer();
        //
        string tId = "Thread JOB Consumer #";
        tId += intToStr(z);
        //
        jConsumer[z].setThreadId(tId);
        DATA_INFO_VAL("Tread Identifier", *jConsumer[z].getThreadId());
        retCode = const_cast<ReturnCode*>(jConsumer[z].setJobSharedQueue(sharedQueue));
        TEST_EQ(1,"Job Consumer","retCode = jConsumer->setJobSharedQueue(sharedQueue); - expected success","Successfull Job Shared Queue Inizialization", retCode->code, SUCCESS);
        delete retCode;
        retCode = const_cast<ReturnCode*>(jConsumer[z].setReportSharedQueue(reportQueue));
        TEST_EQ(2,"Job Consumer","retCode = jConsumer->setReportSharedQueue(reportQueue); - expected success","Successfull Repor Shared Queue Inizialization", retCode->code, SUCCESS);
        delete retCode;
        jConsumer[z].start(); //expected to wait until the 1st job is available on the queue
    }
sleep(20);
    string tId = "";
    /// REPORT CONSUMER
//    ReportConsumer* rConsumer = new ReportConsumer();
//    tId = "Thread REPORT Consumer";
//    rConsumer->setThreadId(tId);
//    DATA_INFO_VAL("Tread Identifier", *rConsumer->getThreadId());
//    retCode = const_cast<ReturnCode*>(rConsumer->setReportSharedQueue(reportQueue));
//    TEST_EQ(6,"Job Consumer","retCode = rConsumer->setReportSharedQueue(reportQueue); - expected success","Successfull Repor Shared Queue Inizialization", retCode->code, SUCCESS);
//    delete retCode;
//    rConsumer->start(); //expected to wait until the 1st job is available on the queue

    /// JOB PRODUCER
    JobProducer* jProducer = new JobProducer();
    tId = "Thread JOB Producer";
    jProducer->setThreadId(tId);
    DATA_INFO_VAL("Tread Identifier", *jProducer->getThreadId());
    retCode = const_cast<ReturnCode*>(jProducer->setJobSharedQueue(sharedQueue));
    TEST_EQ(3,"Job Producer","retCode = jProducer->setJobSharedQueue(sharedQueue); - expected success","Successfull Shared Queue Inizialization", retCode->code, SUCCESS);
    delete retCode;
//    jProducer->start();
    DATA_INFO("Going to sleep for 1 seconds...");
    // loading list
    list<TestCase*>* listOfTC = new list<TestCase*>();                          //list of Test Cases
    for(int idx = 0; idx < nrOfTestCases; idx++) {
        //load new Test Cases
        listOfTC->push_back(&tCase[idx]);
    }
    DATA_INFO_VAL("Publishing Test Case Set #", 1);
//    retCode = const_cast<ReturnCode*>(jProducer->loadTestCases(listOfTC));
    TEST_EQ(5,"Job Producer","retCode = jProducer->loadTestCases(listOfTC)); - expected success","Successfull List of Test Cases Initialization", retCode->code, SUCCESS);
    delete retCode;

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

    jProducer->join();
    for(int i = 0; i < nrOfThreadConsumer; i++) {
        jConsumer[i].join();
    }

    /// DELETE
    if(jProducer != NULL)
        delete jProducer;
    if(jConsumer != NULL) {
        delete [] jConsumer;
    }
//    if(rConsumer != NULL)
//        delete rConsumer;
    //
    delete listOfTC;
    delete sharedQueue;
    delete reportQueue;
    delete tbCfg;
    //
    delete [] ctxObj;
    delete [] cSetItem;
    delete [] cRunItem;
    delete [] ctdItem;
    delete []  tCase;
    //
    delete [] aVar;
    delete [] bVar;

	return 0;
}
