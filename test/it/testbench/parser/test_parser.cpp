#include <parser.h>


using namespace it::testbench::parser;

int main(int argc, char* argv[]) {

    /**
     * STATE MACHINE TESTING
     */
    cout << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout << "\n+++ STATE MACHINE TESTING                                                        +++";
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    ReturnCode* retCode = new ReturnCode;
    ParserState* pState = new ParserState();
    ParserState* retState = pState->init(retCode);
    TEST_EQ(1,"State Machine Testing","pState->init(retCode)","FSM init() - from mother class", (retCode->code == SUCCESS),1);
    TEST_EQ(2,"State Machine Testing","pState->init(retCode)","FSM init() - from mother class", retState->isFSMInitialized(),1);
    //
    Configuration* cfg = new Configuration;
    cfg->URI = "home/hailpam/Developments/c++-workspace/bla.txt";
    cfg->fileName = "bla.txt";
    cfg->filePath =  "home/hailpam/Developments/c++-workspace";
    cfg->fileFormat = "TXT";
    string* loadRes = new string("BLAH");
    try {
        pState->open(cfg, loadRes, retCode);
        TEST_EQ(2,"State Machine Testing","pState->open(cfg, loadRes, retCode)","FSM init() - from mother class - expected exception - error", 1,-1);
    }catch(TestFrameworkException& ex) {
        TEST_EQ(2,"State Machine Testing","pState->open(cfg, loadRes, retCode)","FSM init() - from mother class - expected exception", 1, 1);
     }
     //
    ParserInitialized* pIState = new ParserInitialized();
    TEST_EQ(3,"State Machine Testing","pIState->isFSMInitialized()","FSM inited - from child class", pIState->isFSMInitialized(),1);
    retState = pIState->open(cfg, loadRes, retCode);
    TEST_EQ(4,"State Machine Testing","retState = pIState->open(cfg, loadRes, retCode)","open resource - from child class", (retCode->code == SUCCESS),1);
    //
    try {
        retState->open(cfg, loadRes, retCode);
        TEST_EQ(5,"State Machine Testing","retState->open(cfg, loadRes, retCode)","open resource - expected exception - error", 1,-1);
    }catch(TestFrameworkException& ex) {
        TEST_EQ(6,"State Machine Testing","retState->open(cfg, loadRes, retCode)","open resource - expected exception", 1, 1);
     }
    //
    TestBench* tBench = new TestBench;
    tBench->testPlanNr = 1111;
    tBench->testBenchId = "TestBench";
    //ParserOpened* pOState = reinterpret_cast<ParserOpened*>(retState);
    ParserState* pOState = retState;
    retState = pOState->parse(loadRes, tBench, retCode);
    TEST_EQ(7,"State Machine Testing","retState = pOState->parse(loadRes, tBench, retCode);","parse resource", (retCode->code == SUCCESS), 1);
    try {
         ParserState* pPState = retState;
         ParserState* errState = pPState->error(retCode);
         TEST_EQ(8,"State Machine Testing","retState->error(retCode);","error handling - FSM reset procedure", retCode->code, SUCCESS);
         errState ->reset(retCode);
         TEST_EQ(9,"State Machine Testing","retState->reset(retCode);","error handling - FSM successfully reset", retCode->code, SUCCESS);
         delete errState;
     }catch(TestFrameworkException& exception) {
         DATA_INFO(string(exception.what()));
         TEST_EQ(9,"State Machine Testing","retState->open/resetretCode)","error handling - FSM reset procedure - error", 1,-1);
      }
    //
    retState = retState->validate(tBench, retCode);
    TEST_EQ(10,"State Machine Testing","retState = pOState->parse(loadRes, tBench, retCode);","parse resource", (retCode->code == SUCCESS), 1);
    // force open on an Invalid state -->> test the recover procedure
    try {
        retState->open(cfg, loadRes, retCode);
        TEST_EQ(11,"State Machine Testing","retState->open(cfg, loadRes, retCode)","open resource - expected exception - error", 1,-1);
    }catch(TestFrameworkException& ex) {
        TEST_EQ(11,"State Machine Testing","retState->open(cfg, loadRes, retCode)","open resource - expected exception", 1, 1);
     }


    delete retCode;
    delete pState;
    delete cfg;
    delete pIState;
    delete retState;
    delete tBench;

	return 0;
}
