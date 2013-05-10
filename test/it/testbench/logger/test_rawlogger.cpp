#include <rawlogger.h>
#include <debug.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace it::testbench::logger;

const int THD_NUM = 100;    /* Number of threads writing to log */
const int MSG_NUM = 1000;   /* Number of messages sent by each thread */

void* log_bombing_function(void *arg){
    /**
     * Get the thread index from the caller and
     * initialize all local variables
     */
    int thd_idx = *((int*)arg);
    delete (int*)arg;
    stringstream strStream;
    strStream.str(string());
    RawLogger *log = RawLogger::getInstance();
    /**
     * Storm the log with messages and then return
     */
    for (int i = 0; i < MSG_NUM; i++) {
        strStream <<"thread " <<thd_idx <<": message " <<i;
        log->logD(strStream.str());
        strStream.str(string());
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    /**
     * Setup: prepare strings with filename and messages to log
     */
    string goodLogFile = "test_rawlogger.log";
    string badLogFile = "wrong/incorrect/test_rawlogger.log";
    string traceMsg = "this is a Trace level message";
    string debugMsg = "this is a Debug level message";
    string infoMsg = "this is an Information level message";
    string warningMsg = "this is a Warning level message";
    string errorMsg = "this is an Error level message";
    string fatalMsg = "this is a Fatal level message";
    RawLogger *log;

    /**
     * getInstance() from uninitialized RawLogger
     *
     * Expected value: 0
     */
    log = RawLogger::getInstance();
    PRINT("getInstance() from uninitialized RawLogger");
    PRINT("    returned pointer: " <<log);
    ASSERT_EQUAL(log, 0);

    /**
     * getInstance(logFile) performs lazy initialization
     * with wrong path/filename
     *
     * Expected value: 0
     */
    log = RawLogger::getInstance(badLogFile);
    PRINT("getInstance(file) with bad filename");
    PRINT("    returned pointer: " <<log);
    ASSERT_EQUAL(log, 0);

    /**
     * getInstance(logFile) performs lazy initialization
     * with correct path/filename
     *
     * Expected value: &RawLogger
     */
    log = RawLogger::getInstance(goodLogFile);
    PRINT("getInstance(file) with good filename");
    PRINT("    returned pointer: " <<log);
    ASSERT_NOT_EQUAL(log, 0);

    /**
     * logT, logD, logI
     *
     * Expected value: T/D/I messages logged correctly on file
     */
    log->logT(traceMsg);
    log->logD(debugMsg);
    log->logI(infoMsg);
    PRINT("log Trace/Debug/Info");
    PRINT("    >> check if they have been written on file");

    /**
     * drop &RawLogger, call getInstance() from initialized RawLogger
     *
     * Expected value: &RawLogger
     */
    log = 0;
    log = RawLogger::getInstance();
    PRINT("getInstance(file) from initialized RawLogger");
    PRINT("    returned pointer: " <<log);
    ASSERT_NOT_EQUAL(log, 0);

    /**
     * logW, logE, logF
     *
     * Expected value: W/E/F messages logged correctly on file
     */
    log->logW(warningMsg);
    log->logE(errorMsg);
    log->logF(fatalMsg);
    PRINT("log Warning/Error/Fatal");
    PRINT("    >> check if they have been written on file");

    PRINT("   --------------------   ");
    /**
     * Concurrency test: launch N threads that will storm the log
     */

    /**
     * Start THD_NUM threads successfully
     *
     * Expected value: for() exist when thd_idx == THD_NUM
     */
    stringstream strStream;
    strStream.str(string());
    pthread_t logThread[THD_NUM];
    int thd_idx;
    for (thd_idx = 0; thd_idx < THD_NUM; thd_idx++){
        int *idx = new int;
        *idx = thd_idx;
        if (pthread_create(&logThread[thd_idx], 0, log_bombing_function, (void*) idx) < 0)
            break;
        strStream <<"thread " <<thd_idx <<" has started";
        log->logD(strStream.str());
        strStream.str(string());
    }
    PRINT("start THD_NUM threads successfully");
    ASSERT_EQUAL(thd_idx, THD_NUM);

    /**
     * Join all launched threads
     */
    strStream.str(string());
    int thd_jn;
    for (thd_jn = 0; thd_jn < thd_idx; thd_jn++){
        if (pthread_join(logThread[thd_jn], 0) < 0)
            break;
        strStream <<"thread " <<thd_jn <<" has joined";
        log->logD(strStream.str());
        strStream.str(string());
    }
    PRINT("join all started threads");
    ASSERT_EQUAL(thd_jn, thd_idx);

    return 0;
}
