#include <fsmparser.h>


namespace it
{
namespace testbench
{
namespace parser
{

/// PARSER STATE
ParserState::ParserState() : stateId("Uninitialized"), unInitialized(true) {}
ParserState::~ParserState() {/* Do nothing */}


ParserState* ParserState::init(ReturnCode* report) throw (TestFrameworkException)
{
    if(unInitialized) {
        DATA_INFO("Parser not yet Initialized, ready to be initialized");
        ParserInitialized* initStatus = new ParserInitialized();
        unInitialized = false;
        //
        report->code = SUCCESS;
        report->desc = "Parser Successfully Initialized";
        //
        DATA_INFO("Parser successfully Initialized");
        return initStatus;
    }else
        throw new TestFrameworkException("FSM already Initialized: trigger not allowed");
}

bool ParserState::isFSMInitialized()
{
    return !unInitialized;
}

ParserState* ParserState::open(const Configuration* cfg, string* cfgStream, ReturnCode* report) throw (TestFrameworkException)
{
    throw TestFrameworkException("Unitialized/Ivalid FSM state: make sure to get the FSM Initialized and to use proper triggers");
}

ParserState* ParserState::parse(const string* loadedCfg, TestBench* res, ReturnCode* report) throw (TestFrameworkException)
{
    throw TestFrameworkException("Unitialized/Ivalid FSM state: make sure to get the FSM Initialized and to use proper triggers");
}

ParserState* ParserState::validate(const TestBench* loadedCfg, ReturnCode* report) throw (TestFrameworkException)
{
    throw TestFrameworkException("Unitialized/Ivalid FSM state: make sure to get the FSM Initialized and to use proper triggers");
}

ParserState* ParserState::reset(ReturnCode* report) throw (TestFrameworkException)
{
    throw TestFrameworkException("Unitialized/Ivalid FSM state: make sure to get the FSM Initialized and to use proper triggers");
}

ParserState* ParserState::error(ReturnCode* report) throw (TestFrameworkException)
{
    throw TestFrameworkException("Unitialized/Ivalid FSM state: make sure to get the FSM Initialized and to use proper triggers");
}

/// SPECIFIC STATES
/// PARSERINITIALIZED STATE
ParserInitialized::ParserInitialized() : ParserState()
{
    ParserState::stateId = "Initialized";
    unInitialized = false;
}
ParserInitialized::~ParserInitialized() {/* Do nothing */}

ParserState* ParserInitialized::open(const Configuration* cfg, string* cfgStream, ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Open correctly served");
    DATA_INFO_VAL("Configuration ", cfg->URI);
    DATA_INFO_VAL("Configuration ", cfg->filePath);
    DATA_INFO_VAL("Configuration ", cfg->fileName);
    DATA_INFO_VAL("Configuration ", cfg->fileFormat);
    *cfgStream = "OK";
    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserOpened();

    return newState;
}

/// PARSEROPENED STATE
ParserOpened::ParserOpened() : ParserState()
{
    ParserState::stateId = "Resource Opened";
    unInitialized = false;
}
ParserOpened::~ParserOpened() {/* Do nothing */}

ParserState* ParserOpened::parse(const string* loadedCfg, TestBench* res, ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Parse correctly served");
    DATA_INFO_VAL("Configuration ", res->testPlanNr);
    DATA_INFO_VAL("Configuration ", res->testBenchId);

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserParsed();

    return newState;
}

ParserState* ParserOpened::error(ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Error correctly served");

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserFailed();

    return newState;
}

/// PARSEDPARSED STATE
ParserParsed::ParserParsed() : ParserState()
{
    ParserState::stateId = "Resource Parsed";
    unInitialized = false;
}
ParserParsed::~ParserParsed() {/* Do nothing */}

ParserState* ParserParsed::validate(const TestBench* loadedCfg, ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Open correctly served");
    DATA_INFO_VAL("Configuration ", loadedCfg->testPlanNr);
    DATA_INFO_VAL("Configuration ", loadedCfg->testBenchId);

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserValidated();

    return newState;
}

ParserState* ParserParsed::error(ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Error correctly served");

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserFailed();

    return newState;
}

/// PARSERVALIDATED STATE
ParserValidated::ParserValidated() : ParserState()
{
    ParserState::stateId = "Resource Validated";
    unInitialized = false;
}
ParserValidated::~ParserValidated() {/* Do nothing */}

ParserState* ParserValidated::reset(ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Reset correctly served");

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    ParserState* newState = new ParserInitialized();

    return newState;
}

/// PARSEDFAILED STATE
ParserFailed::ParserFailed() : ParserState()
{
    ParserState::stateId = "Runtime Failure";
    unInitialized = false;
}
ParserFailed::~ParserFailed() {/* Do nothing */}

ParserState* ParserFailed::reset(ReturnCode* report) throw (TestFrameworkException)
{
    DATA_INFO("Reset correctly served");

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";
    ParserState* newState = new ParserInitialized();

    return newState;
}


}   /* PARSER */
}   /* TESTBENCH */
}   /* IT */
