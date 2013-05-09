#include <rawlogger.h>
#include <debug.h>
#include <string>

using namespace std;
using namespace it::testbench::logger;

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
    DEBUG("RawLogger TI: getInstance() from uninitialized RawLogger");
    DEBUG("    returned pointer: " <<log);
    ASSERT_EQUAL(log, 0);

    /**
     * getInstance(logFile) performs lazy initialization
     * with wrong path/filename
     *
     * Expected value: 0
     */
    log = RawLogger::getInstance(badLogFile);
    DEBUG("RawLogger TI: getInstance(file) with bad filename");
    DEBUG("    returned pointer: " <<log);
    ASSERT_EQUAL(log, 0);

    /**
     * getInstance(logFile) performs lazy initialization
     * with correct path/filename
     *
     * Expected value: &RawLogger
     */
    log = RawLogger::getInstance(goodLogFile);
    DEBUG("RawLogger TI: getInstance(file) with good filename");
    DEBUG("    returned pointer: " <<log);
    ASSERT_NOT_EQUAL(log, 0);

    /**
     * logT, logD, logI
     *
     * Expected value: T/D/I messages logged correctly on file
     */
    log->logT(traceMsg);
    log->logD(debugMsg);
    log->logI(infoMsg);
    DEBUG("Rawlogger TI: log Trace/Debug/Info");
    DEBUG("    >> check if they have been written on file");

    /**
     * drop &RawLogger, call getInstance() from initialized RawLogger
     *
     * Expected value: &RawLogger
     */
    log = 0;
    log = RawLogger::getInstance();
    DEBUG("RawLogger TI: getInstance(file) from initialized RawLogger");
    DEBUG("    returned pointer: " <<log);
    ASSERT_NOT_EQUAL(log, 0);

    /**
     * logW, logE, logF
     *
     * Expected value: W/E/F messages logged correctly on file
     */
    log->logW(warningMsg);
    log->logE(errorMsg);
    log->logF(fatalMsg);
    DEBUG("Rawlogger TI: log Warning/Error/Fatal");
    DEBUG("    >> check if they have been written on file");

    return 0;
}
