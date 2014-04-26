#include <rte.h>


namespace it
{
namespace testbench
{
namespace rte
{


RuntimeEngine::RuntimeEngine() : Subject()
{
    /* do nothing */
    jobQueue = new SynchronizedQueue<Job*>();
    jobQueue->setLabel("Shared Job Queue");
    reportQueue = new SynchronizedQueue<Report*>();
    reportQueue->setLabel("Shared Report Queue");

    jobProd = new JobProducer();
    jobCons = new list<JobConsumer*>();
    repCons = new ReportConsumer();

    poolSize = 0;
}

RuntimeEngine::~RuntimeEngine()
{
    // TODO itearate on the queue to destroy any Job or Report pointer
    delete jobQueue;
    delete reportQueue;
    delete jobProd;
    delete repCons;
    list<JobConsumer*>::iterator listItr;
    for(listItr = jobCons->begin(); listItr != jobCons->end(); ++listItr) {
        //normally, this should destroy the contained elements calling respective destructors
        jobCons->erase(listItr);
    }
    delete jobCons;
}

ReturnCode* RuntimeEngine::initEngine(const unsigned int nrOfWorkers)
{
    //TODO : start thread when the synchronization issue is solved
    //TODO : register observer to report consumer
    #warning TODO : start thread when the synchronization issue is solved
    ReturnCode* retCode = new ReturnCode;
    unsigned int lowerBound = 0;
    if(nrOfWorkers == lowerBound || nrOfWorkers > NR_MAX_OF_THREADS) {
        retCode->code = ERROR;
        retCode->desc = "Provided a wrong setting: the number of worker thread must be in (0,256]";
        DATA_ERR_VAL("Provided a wrong setting: the number of worker thread must be in (0,256] #", nrOfWorkers);

        return retCode;
    }
    //setting up JobProducer and ReportConsumer
    DATA_INFO("Job Producer setting up... ");
    jobProd->setJobSharedQueue(jobQueue);
//    jobProd->start();
    DATA_INFO("... Job Producer detached.");
    DATA_INFO("Report Consumer setting up... ");
    DATA_INFO_VAL("Report Queue", reportQueue->getLabel());
    repCons->setReportSharedQueue(reportQueue);
//    repCons->start();
    DATA_INFO("... Report Consumer detached.");
    //creating pool of worker threads
    poolSize = nrOfWorkers;
    for(unsigned int i = 0; i < nrOfWorkers; i++) {
        DATA_INFO_VAL("Job Consumer setting up... ", i);
        JobConsumer* jCons = new JobConsumer();
        jCons->setJobSharedQueue(jobQueue);
        jCons->setReportSharedQueue(reportQueue);
        string tId = "Job Consumer #";
        tId += i;
        DATA_INFO_VAL("  Job Consumer Id", tId);
        jCons->setThreadId(tId);
//        jCons->start();
        DATA_INFO_VAL("... Job Consumer detached", i);
        jobCons->push_back(jCons);
    }
    //
    retCode->code = SUCCESS;
    retCode->desc = "Fake Initialization";

    return retCode;
}

ReturnCode* RuntimeEngine::destroyEngine()
{
    //TODO destroy threads : how to destroy consumers?
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Fake Destruction";

    return retCode;
}


ReturnCode* RuntimeEngine::launchTestPlan(const TestBenchConfiguration* tbCfg, const string& tPlanId) throw (TestFrameworkException)
{
    ReturnCode* retCode = new ReturnCode;
    if(tbCfg == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: testbench configuration cannot be used";
        DATA_ERR_VAL("Provided a NULL Pointer in Input as testbench configuration", tbCfg);

        return retCode;
    }
    if(tPlanId.empty()) {
        retCode->code = ERROR;
        retCode->desc = "Blank string in Input: test plan cannot be searched";
        DATA_ERR_VAL("Provided a Blank string in Input as test plan indentifier", tbCfg);

        return retCode;
    }
    list<TestCase*>* listOfTC = new list<TestCase*>();
    //1. look for Test Plan (if more than one)
    TestBenchConfiguration* locTbCfg = const_cast<TestBenchConfiguration*>(tbCfg);
    string* sessId = const_cast<string*>(locTbCfg->getSessionId());
    DATA_INFO_VAL("Retrieved Testbench Session Id", *sessId);
    TestPlan* tPlan = const_cast<TestPlan*>(locTbCfg->retrieveTestPlan(&tPlanId));
    if(tPlan == NULL) {
        DATA_ERR_VAL("NULL Pointer instead of an expected Test Plan", -1);
        throw TestFrameworkException("NULL Pointer instead of an expected Test Plan");
    }
    unsigned int nrOfTC = tPlan->getNrOfTestCases();
    DATA_INFO_VAL("Test Plan has a bunch of Test Cases #", nrOfTC);
    Range* tcRange = const_cast<Range*>(locTbCfg->retrieveRange(&tPlanId));
    DATA_INFO_VAL("Test Case Range from #", tcRange->from);
    DATA_INFO_VAL("Test Case Range to #", tcRange->to);
    //2. load a Test Case list to pass to the Job Producer
    unsigned int startIdx;
    unsigned int endIdx;
    if(tcRange == NULL || (tcRange->from == tcRange->to && tcRange->from == 0)) {
        startIdx = 0;
        endIdx = nrOfTC;
    }else {
        startIdx = tcRange->from;
        endIdx = tcRange->to;
     }
    for(unsigned int i = startIdx; i < endIdx; i++) {
        listOfTC->push_back(const_cast<TestCase*>(tPlan->retrieveTestCase(i)));
        DATA_INFO_VAL("Retrieved and Loaded Test Case #", listOfTC->back()->getTestCaseNumber());
    }
    //TODO  case of multiple ranges and multiple test plans
    ReturnCode* outcome = const_cast<ReturnCode*>(jobProd->loadTestCases(listOfTC));
    if(outcome->code == ERROR) {
        delete retCode;
        string tmp = outcome->desc;
        delete outcome;
        DATA_ERR_VAL("Error occurred in loading Test Cases", tmp);
        throw TestFrameworkException("Error occurred in loading Test Cases ["+tmp+"]");
    }
    //3. resume the Job Producer to start pushing test cases
//    jobProd->resume();
    //
    retCode->code = SUCCESS;
    retCode->desc = "Bunch of new Test Cases has been loaded: Job Producer is working on them";
    DATA_INFO("Test Cases from Testbench Configuration correctly scheduled to be run");

    return retCode;
}

void RuntimeEngine::notify(Report* report)
{
    //notification from report consumer -->> notify all observers
    this->notifyObservers(report);
}

const int& RuntimeEngine::actualPoolSize()
{
    return poolSize;
}

}   /* RTE */
}   /* TESTBENCH */
}   /* IT */
