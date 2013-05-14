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
    DATA_INFO("==================================");
    DATA_INFO_VAL("         URI::", cfg->URI);
    DATA_INFO_VAL("   File path::", cfg->filePath);
    DATA_INFO_VAL("   File name::", cfg->fileName);
    DATA_INFO_VAL(" File format::", cfg->fileFormat);
    DATA_INFO("==================================");

    report->code = SUCCESS;
    report->desc = "FAKE Implementation";

    RawFSManager* fsMng = RawFSManager::getInstance();
    FormattedResource res;
    res.ext = cfg->fileFormat;
    res.name = cfg->fileName;
    try {
        fsMng->read(&res);
        *cfgStream = res.content;
    }catch(TestFrameworkException& exception)
     {
        DATA_ERR_VAL("Exception occurred in opening", (cfg->fileName + cfg->fileFormat));
        unInitialized = false;      // to let a new configuration
        throw TestFrameworkException("Exception occurred in opening ["+cfg->URI+"]"+" - reason ["+string(exception.what())+"]");
     }
    ParserState* newState = new ParserOpened();
    //
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

    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(*loadedCfg, root, false);

    if(not parsedSuccess) {
        DATA_ERR_VAL("Failed to Parse the FS stream previously loaded", reader.getFormatedErrorMessages());
        report->code = ERROR;
        report->desc = "Severe Error occurred in parsing the FS stream";

        throw TestFrameworkException("Severe Error occurred in parsing the FS stream - ["+reader.getFormatedErrorMessages()+"]");
    }

    // Configuration File actual parsing
    // TODO : to be implemented with recursion
    #warning TODO : to be implemented with recursion
    try {
        const Json::Value tBench = root["test_bench"];
        //
        cout << "-O" << endl;
        cout << " |" << endl;
        cout << " +-(\"test_bench\")-" << endl;
        cout << " |" << endl;
        const Json::Value id = tBench["identifier"];
        cout << " +-->" << "[\"idenfier\"][" << id.asString() << "]" << endl;
        res->testBenchId = id.asString();                       // set test bench id
        cout << " |" << endl;
        const Json::Value bDir = tBench["base_dir"];
        cout << " +-->" << "[\"base_dir\"][" << bDir.asString() << "]" << endl;
        cout << " |" << endl;
        const Json::Value nrOfThreads = tBench["nr_of_threads"];
        cout << " +-->" << "[\"nr_of_threads\"][" << nrOfThreads.asInt() << "]" << endl;
        cout << " |" << endl;
        const Json::Value tPlanNr = tBench["test_plan_nr"];
        cout << " +-->" << "[\"test_plan_nr\"][" << tPlanNr.asInt() << "]" << endl;
        cout << " |" << endl;
        res->testPlanNr = tPlanNr.asInt();                      // set the number of test plans
        res->tpArray = new ParserResource[tPlanNr.asInt()];     // initialize an array of parsed resources
        const Json::Value cOpts = tBench["console_options"];
        cout << " +--" << "-(\"console_options\")-" << endl;
        cout << " |" << endl;
        cout << " +------+" << endl;
        cout << " \t|" << endl;
        const Json::Value lSep = cOpts["line_separator"];
        cout << " \t+-->" << "[\"line_separator\"]" << "[" << lSep.asString() << "]" << endl;
        cout << " \t|" << endl;
        const Json::Value cSep = cOpts["column_separator"];
        cout << " \t+-->" << "[\"column_separator\"]" << "[" << cSep.asString() << "]" << endl;
        cout << " \t|" << endl;
        const Json::Value tNrSpaces = cOpts["tab_nr_spaces"];
        cout << " \t+-->" << "[\"tab_nr_spaces\"]" << "[" << tNrSpaces.asInt() << "]" << endl;
        cout << " \t|" << endl;
        const Json::Value beautified = cOpts["beautified"];
        cout << " \t+-->" << "[\"beautified\"]" << "[" << beautified.asBool() << "]" << endl;
        cout << " \t|" << endl;
        const Json::Value vBracked = cOpts["value_bracked"];
        cout << " \t+-->" << "[\"value_bracked\"]" << "[" << vBracked.asString() << "]" << endl;
        cout << " \t|" << endl;
        cout << " +------+" << endl;
        cout << " |" << endl;
        const Json::Value tPlans = tBench["test_plans"];
        cout << " +--" << "-(\"test_plans\")-" << endl;
        cout << " |" << endl;
        cout << " +-------+" << endl;
        // retrieving test plans
        for(unsigned int i = 0; i < tPlans.size(); i++) {

            const Json::Value tPlansArr = tPlans[i];
            cout << " \t|" << endl;
            cout << " \t+->>" << "testPlan[" << i << "]" << endl;
            cout << " \t|" << endl;
            const Json::Value tPlan = tPlansArr["test_plan"];
            cout << " \t+-->" << "[\"test_plan\"][size::" << tPlans.size() << "]" << endl;
            cout << " \t|" << endl;
            const Json::Value tPlanId = tPlan["test_plan_id"];
            cout << " \t+-->" << "[\"test_plan_id\"]" << "[" << tPlanId.asString() << "]" << endl;
            cout << " \t|" << endl;
            res->tpArray[i].testPlanId = tPlanId.asString();       // set test case number
            const Json::Value ctxObj = tPlan["context_object"];
            cout << " \t+-->" << "[\"context_object\"]" << "[" << ctxObj.asString() << "]" << endl;
            cout << " \t|" << endl;
            const Json::Value tcNr = tPlan["test_case_nr"];
            cout << " \t+-->" << "[\"test_case_nr\"]" << "[" << tcNr.asInt() << "]" << endl;
            cout << " \t|" << endl;
            res->tpArray[i].testCaserNr = tcNr.asInt();            // set test case number
            const Json::Value tCases = tPlan["test_cases"];
            cout << " \t+--" << "-(\"test_cases\")-" << endl;
            cout << " \t|" << endl;
            cout << " \t+-------+" << endl;
            // retrieving test cases
            for(unsigned int j = 0; j < tCases.size(); j++) {

                const Json::Value tCasesArr = tCases[j];
                cout << " \t\t+->>" << "testCases[" << 0 << "]"<< endl;
                cout << " \t\t|" << endl;
                const Json::Value tCase = tCasesArr["test_case"];
                cout << " \t\t+-->" << "[\"test_case\"][size::" << tCase.size() << "]" << endl;
                cout << " \t\t|" << endl;
                const Json::Value number = tCase["number"];
                cout << " \t\t+-->" << "[\"number\"][" <<  number.asInt() << "]" << endl;
                cout << " \t\t|" << endl;
                const Json::Value initItem = tCase["init_item"];
                cout << " \t\t+-->" << "[\"init_item\"][" <<  initItem.asString() << "]" << endl;
                cout << " \t\t|" << endl;
                const Json::Value tearDownItem = tCase["teard_down_item"];
                cout << " \t\t+-->" << "[\"teard_down_item\"][" << tearDownItem.asString() << "]" << endl;
                cout << " \t\t|" << endl;
                const Json::Value rItems = tCase["runnable_items"];
                cout << " \t\t+-->" << "-(\"runnable_items\")-" << endl;
                cout << " \t\t|" << endl;
                cout << " \t\t+-------+" << endl;
                // retrieving runnable items
                for(unsigned int z = 0; z < rItems.size(); z++) {

                    const Json::Value rItem = rItems [z];
                    cout << " \t\t\t+-->" << "[" <<  rItem.asString() << "]" << endl;
                    cout << " \t\t\t|" << endl;
                } /* runnable items */
                cout << " \t\t+-------+" << endl;
                const Json::Value ranges = tCase["ranges"];
                cout << " \t\t|" << endl;
                res->tpArray[i].rangeArray = new Range[ranges.size()];     // set the execution ranges
                cout << " \t\t+-->" << "-(\"ranges\")-" << endl;
                cout << " \t\t|" << endl;
                cout << " \t\t+-------+" << endl;
                // retrieving execution ranges
                for(unsigned int w = 0; w < ranges.size(); w++) {

                    const Json::Value rangesArr = ranges[w];
                    cout << " \t\t\t|" << endl;
                    const Json::Value from = rangesArr["from"];
                    cout << " \t\t\t+-->" << "[\"from\"][" <<  from.asInt() << "]" << endl;
                    cout << " \t\t\t|" << endl;
                    res->tpArray[i].rangeArray[w].from = from.asInt();      // set the 'from' value
                    const Json::Value to = rangesArr["to"];
                    cout << " \t\t\t|-->" << "[\"to\"][" <<  to.asInt() << "]" << endl;
                    res->tpArray[i].rangeArray[w].to = to.asInt();          // set the 'to' value

                } /* ranges */
                cout << " \t\t\t^" << endl;

            } /* test cases */

        } /* test plans */

    }catch(exception& exception) {
        report->code = ERROR;
        report->desc = "Error occurred during the parsing: unable to proceed";
        DATA_ERR_VAL("Error occurred during the parsing: unable to proceed", string(exception.what()));

        throw TestFrameworkException("Severe Error occurred during the parging: unable to proceed - ["+string(exception.what())+"]");
    }
    report->code = SUCCESS;
    report->desc = "Configuration correctly parsed";
    DATA_INFO("Configuration read from FS stream correctly parsed: ready for the next step");
    //
    ParserState* newState = new ParserParsed();
    //
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
    TestBench* locCfg = const_cast<TestBench*>(loadedCfg);
    DATA_INFO("=== Loaded Test Bench Configuration ===");
    DATA_INFO("=======================================");
    DATA_INFO_VAL("Test plan Nr ", loadedCfg->testPlanNr);
    DATA_INFO_VAL("Testbench Id ", loadedCfg->testBenchId);

    if(loadedCfg->testPlanNr == 0 || loadedCfg->testBenchId.empty() || loadedCfg->tpArray == 0) {
        DATA_ERR_VAL("Loaded Testbench resource got the Id and number of Test Plan(s) 0: unable to proceed", -1);
        //
        report->code = ERROR;
        report->desc = "Loaded Testbench resource got the Id and number of Test Plan(s) 0: unable to proceed";
        //
        throw TestFrameworkException("Loaded Testbench resource got the Id and number of Test Plan(s) 0: unable to proceed");
    }
    // TODO : cross-check the array size for test plans
    #warning TODO : cross-check the array size for test plans

    for(int i = 0; i < loadedCfg->testPlanNr; i++) {
        if(locCfg->tpArray[i].rangeArray == 0 || locCfg->tpArray[i].testCaserNr == 0 || locCfg->tpArray[i].testPlanId.empty()) {
            DATA_ERR_VAL("Loaded Testbench resource got the Id and number of Test Plan(s) 0: unable to proceed", -1);
            //
            report->code = ERROR;
            report->desc = "Loaded Test Plan(s) got not specified vital attributes (Nr of Test Cases, Test Plan Id, etc.) : unable to proceed";
            //
            throw TestFrameworkException("Loaded Test Plan(s) got not specified vital attributes (Nr of Test Cases, Test Plan Id, etc.) : unable to proceed");
        }
    }
    //
    report->code = SUCCESS;
    report->desc = "Testbench Configuration (previously loaded and parsed) has been correctly validated: configuration ready to be used";
    //
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
