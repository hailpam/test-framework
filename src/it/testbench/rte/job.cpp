#include <job.h>


namespace it
{
namespace testbench
{
namespace rte
{


Job::Job() : tCase(NULL), tCaseExecuted(false)
{
}

Job::~Job() {/* do nothing */}

ReturnCode* Job::executeTestCase() {
    ReturnCode* retCode = new ReturnCode;
    if(tCase == NULL) {
        DATA_ERR_VAL("TestCase not yet set: no execution can be performed", -1);
        retCode->code = ERROR;
        retCode->desc = "It is not allowed to request an execution prior to set the TestCase";

        return retCode;
    }
    //
    try {
            tCase->setupTestCase();
            tCase->runTestCase();
            tCase->tearDownTestCase();
    }catch(TestFrameworkException& exception) {
        DATA_ERR_VAL("Exception Catched", exception.what());
        retCode->code = ERROR;
        retCode->desc = "Error Occurred during the execution of the TestCase";

        return retCode;
     }
     DATA_INFO("Test Case successfully executed");
    //
    retCode->code = SUCCESS;
    retCode->desc = "Test Case successfully executed";
    tCaseExecuted = true;

    return retCode;
}

ReturnCode* Job::generateReport(Report* genReport) {
    ReturnCode* retCode = new ReturnCode;
    if(!tCaseExecuted) {
        DATA_ERR_VAL("TestCase not yet executed: Report cannot be generated", -1);
        retCode->code = ERROR;
        retCode->desc = "It is not allowed to request a Report generation before to execute the TestCase";

        return retCode;
    }
    DATA_INFO("Report successfully generated from executed Test Case");
    //
    genReport = tCase->finalizeReport();
    retCode->code = SUCCESS;
    retCode->desc = "Report has been correctly generated";

    return retCode;
}


ReturnCode* Job::setTestCase(const TestCase* tCase) {
    ReturnCode* retCode = new ReturnCode;
    if(tCase == NULL) {
        DATA_ERR_VAL("NULL Pointer in Input: TestCase cannot be set", -1);
        retCode->code = ERROR;
        retCode->desc = "NULL Pointer in Input: set operation cannot ben performed";

        return retCode;

    }
    //
    this->tCase = const_cast<TestCase*>(tCase);
    retCode->code = SUCCESS;
    retCode->desc = "Test Case correctly set";

    return retCode;
}

}   /* RTE */
}   /* TESTBENCH */
}   /* IT */
