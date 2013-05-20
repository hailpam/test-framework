#include <jobcons.h>

using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace rte
{


JobConsumer::JobConsumer() : Thread()
{
    threadId = "JobConsumer Thread";
    jobQueue = NULL;
    reportQueue = NULL;
    isPaused = false;
    pthread_mutex_init(&stateMutex, NULL);
}

JobConsumer::~JobConsumer()
{
    //pass in input the return value accessible by the father
    pthread_exit((void*) 1);
    pthread_mutex_destroy(&stateMutex);
}

void* JobConsumer::run()
{
    #warning TODO : random NULL pointer to be investigated
    DATA_INFO_VAL("Job Consumer is running... ", threadId);
    ReturnCode* retFromOp;
    int itrConsumer = 0;
    while(isRunning) {
        DATA_INFO_VAL("Waiting for a JOB::Consumer", threadId);
        DATA_INFO_VAL("Loop", itrConsumer);
        Job* retJob = jobQueue->dequeue();
        DATA_INFO_VAL("Got a JOB::Consumer", threadId);
        if(retJob == NULL) {
            DATA_ERR_VAL("Got a NULL Pointer", -1);
            // TODO : an error report to be generated
            continue;
        }
        DATA_INFO_VAL("Job retrieved from Queue", retJob);
        retFromOp = retJob->executeTestCase();
        if(retFromOp->code == SUCCESS) {
            Report* retRep;
            delete retFromOp;
            retFromOp = retJob->generateReport(retRep);
            if(retFromOp->code == SUCCESS)
                reportQueue->enqueue(retRep);
            else
                DATA_ERR_VAL("An Error occurred during the Report generation", retFromOp->desc);
            delete retFromOp;
            // TODO : an error report to be generated
        }else {
            DATA_ERR_VAL("An Error occurred during the execution of Test Case", retFromOp->desc);
            // TODO : an error report to be generated
        }
        itrConsumer++;
//        delete retJob;
    }
    DATA_INFO("... Job Consumer is quitting.");
    //
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Job Consumer exited normally: business logic correclty implemented";

    return retCode;
}

void JobConsumer::killIt()
{
    isRunning = false;
    pthread_mutex_unlock(&stateMutex);
}

const ReturnCode* JobConsumer::setJobSharedQueue(SynchronizedQueue<Job*>* sharedQueue)
{
    ReturnCode* retCode = new ReturnCode;
    if(sharedQueue == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: shared Job Queue cannot be initialized";
        DATA_ERR_VAL("NULL Pointer in Input: shared Job Queue cannot be initialized", -1);

        return retCode;
    }
    this->jobQueue = sharedQueue;
    DATA_INFO("Shared Job Queue initialized");
    retCode->code = SUCCESS;
    retCode->desc = "Shared Job Queue correctly initialized";

    return retCode;
}

const ReturnCode* JobConsumer::setReportSharedQueue(SynchronizedQueue<Report*>* sharedQueue)
{
    ReturnCode* retCode = new ReturnCode;
    if(sharedQueue == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: shared Report Queue cannot be initialized";
        DATA_ERR_VAL("NULL Pointer in Input: shared Report Queue cannot be initialized", -1);

        return retCode;
    }
    this->reportQueue = sharedQueue;
    DATA_INFO("Shared Report Queue initialized");
    retCode->code = SUCCESS;
    retCode->desc = "Shared Report Queue correctly initialized";

    return retCode;
}


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */



