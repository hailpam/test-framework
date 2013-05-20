#include <reportcons.h>

using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace rte
{


ReportConsumer::ReportConsumer() : Thread(), Subject()
{
    threadId = "JobProducer Thread";
    reportQueue = NULL;
    isPaused = false;
}

ReportConsumer::~ReportConsumer()
{
    //pass in input the return value accessible by the father
    pthread_exit((void*) 1);
}

void* ReportConsumer::run()
{
    DATA_INFO_VAL("Report Consumer is running... ", threadId);
    ReturnCode* retFromOp;
    int itrConsumer = 0;
    while(isRunning) {
        DATA_INFO_VAL("Waiting for a Report::Consumer", threadId);
        DATA_INFO_VAL("Loop", itrConsumer);
        Report* retReport = reportQueue->dequeue();
        DATA_INFO_VAL("Got a Report::Consumer", threadId);
        DATA_INFO_VAL("Report retrieved form Queue", retReport);
        // 1. format the Report
        // 2. notify the observers
        // 3. write on file the formatted report
        // 4. delete the report
        itrConsumer++;
    }
    DATA_INFO("... Repor Consumer is quitting.");
    //
    ReturnCode* retCode = new ReturnCode;
    retCode->code = SUCCESS;
    retCode->desc = "Report Consumer exited normally: business logic correclty implemented";

    return retCode;
}

void ReportConsumer::killIt()
{
    isRunning = false;
}

const ReturnCode* ReportConsumer::setReportSharedQueue(SynchronizedQueue<Report*>* sharedQueue)
{
    ReturnCode* retCode = new ReturnCode;
    if(sharedQueue == NULL) {
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: shared Report Queue cannot be initialized";
        DATA_ERR_VAL("NULL Pointer in Input: shared Report Queue cannot be initialized", -1);

        return retCode;
    }
    this->reportQueue = reportQueue;
    DATA_INFO("Shared Report Queue initialized");
    retCode->code = SUCCESS;
    retCode->desc = "Shared Report Queue correctly initialized";

    return retCode;
}


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */
