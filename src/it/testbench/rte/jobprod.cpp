#include <jobprod.h>

namespace it
{
namespace testbench
{
namespace rte
{


JobProducer::JobProducer() : Thread()
{
    threadId = "JobProducer Thread";
    sharedQueue = NULL;
    testCases = NULL;
    isPaused = false;
    pthread_mutex_init(&stateMutex, NULL);
}

JobProducer::~JobProducer()
{
    //pass in input the return value accessible by the father
    pthread_exit((void*) 1);
    pthread_mutex_destroy(&stateMutex);
}

void* JobProducer::JobProducer::run()
{
    /*
     * 1. Once started, it's ready to push jobs but,
     * 1.1 it can push iff some test cases have already been loaded
     * 2. In case no test cases have already been loaded,
     * 2.1 it blocks itself on a mutex or condition variable
     * 3. Otherwise,
     * 3.1 it transforms test cases in as many jobs and pushes them on job queue
     */
    DATA_INFO("Job Producer is running... ");
    while(isRunning) {
        if(testCases != NULL) {
            pthread_mutex_lock(&stateMutex);
            // pause when the set of test cases has alrady been transformed in Jobs
            list<TestCase*>::iterator itrList;
            DATA_INFO_VAL("New Cycle of Test Cases ready to be pushed - Test Cases#", testCases->size());
            int idx = 0;
            for(itrList = testCases->begin(); itrList != testCases->end(); itrList++) {
                // create the job from the test case
                Job* tcJob = new Job();
                tcJob->setTestCase(*itrList);
                // push the job on the job queue
                sharedQueue->enqueue(tcJob);
                DATA_INFO_VAL("Job pushed on the Queue", (idx + 1));
    //            itrList = testCases->erase(itrList);
    //            DATA_INFO_VAL("Test Case removed from the List", (idx + 1));
                ++idx;
            }
            testCases->clear();
        }else {
            DATA_INFO("No Test Case has already been provided");
         }
    }
    DATA_INFO("... Job Producer is quitting.");
    //
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Producer exited normally: business logic correclty implemented";

    return retCode;
}

const ReturnCode* JobProducer::setJobSharedQueue(SynchronizedQueue<Job*>* sharedQueue)
{
    ReturnCode* retCode = new ReturnCode;
    if(sharedQueue == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: shared Job Queue cannot be initialized";
        DATA_ERR_VAL("NULL Pointer in Input: shared Job Queue cannot be initialized", -1);

        return retCode;
    }
    this->sharedQueue = sharedQueue;
    DATA_INFO("Shared Job Queue initialized");
    retCode->code = SUCCESS;
    retCode->desc = "Shared Job Queue correctly initialized";

    return retCode;
}

const ReturnCode* JobProducer::pause()
{
    DATA_INFO("Job Producer is going to be stopped (pause)...");
    pthread_mutex_lock(&stateMutex);
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Job Producer is correctly paused";

    return retCode;
}

const ReturnCode* JobProducer::resume()
{
    DATA_INFO("Job Consumer is going to be resumed...");
    pthread_mutex_unlock(&stateMutex);
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Job Consumer is correctly resumed";

    return retCode;
}

void JobProducer::killIt() {
    isRunning = false;
    pthread_mutex_unlock(&stateMutex);
}

const ReturnCode* JobProducer::loadTestCases(list<TestCase*>* tCases)
{
    ReturnCode* retCode = new ReturnCode;
    if(tCases == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: list of Test Cases cannot be initialized";
        DATA_ERR_VAL("NULL Pointer in Input: list of Test Cases cannot be initialized", -1);

        return retCode;
    }
    if(this->testCases != NULL)
        delete this->testCases;     //clean up previously allocated memory
    this->testCases = tCases;
    DATA_INFO("List of Test Cases has been correctly initialized");
    DATA_INFO_VAL("A bunch of new Test Cases is ready to be pushed on Job Queue", tCases->size());
    retCode->code = SUCCESS;
    retCode->desc = "List of Test Cases has been correctly initialized";
    pthread_mutex_unlock(&stateMutex);

    return retCode;
}

}   /* RTE */
}   /* TESTBENCH */
}   /* IT */
