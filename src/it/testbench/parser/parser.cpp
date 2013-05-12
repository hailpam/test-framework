#include <parser.h>

using namespace std;

namespace it
{
namespace testbench
{
namespace parser
{

ParserManager::ParserManager()
{
    loadedCfg = new Configuration;
    currentState = new ParserState();
    loadedStream = new string("");
    tbParsed = new TestBench;
}

ParserManager::~ParserManager()
{
    delete loadedCfg;
    delete currentState;
    delete loadedStream;
    delete tbParsed;
}

void ParserManager::loadConfig(const Configuration& fileCfg) throw (TestFrameworkException)
{
    if(fileCfg.URI.empty() || (fileCfg.filePath.empty() && fileCfg.filePath.empty() && fileCfg.fileFormat.empty())) {
        DATA_ERR_VAL("Provided in Input a Configuration Object badly filled: resource to be loaded not specified", -1);
        throw new TestFrameworkException("Undefined Resource to be loaded");
    }
    if(fileCfg.sessionId.empty()) {
        DATA_ERR_VAL("Provided in Input a Configuration Object badly filled: session Id has not been specified", -1);
        throw new TestFrameworkException("Undefined Session to work in");
    }
    //
    loadedCfg->URI = fileCfg.URI;
    loadedCfg->filePath = fileCfg.filePath;
    loadedCfg->fileName = fileCfg.fileName;
    loadedCfg->fileFormat = fileCfg.fileFormat;
    loadedCfg->sessionId = fileCfg.sessionId;
    //
    ReturnCode retCode;
    ParserState* newState;
    try {
        newState = this->currentState->open(loadedCfg, loadedStream, &retCode);
        if(retCode.code == SUCCESS)
            DATA_INFO_VAL("Stream correctly loaded: dimension #byte", this->loadedStream->size());
        else
            throw new TestFrameworkException(retCode.desc);
        delete this->currentState;
        this->currentState = newState;
    }catch(TestFrameworkException& exception)
     {
         /* failure management/recovery */
         try {
             this->currentState->error(&retCode);
             newState = this->currentState->reset(&retCode);
             delete this->currentState;
             this->currentState = newState;
         }catch(TestFrameworkException& exception) {
             DATA_ERR_VAL("Severe Error occurred in resetting the FSM::"+string(exception.what()), -1);
             throw new TestFrameworkException("ParserManager::loadConfig["+string(exception.what())+"] - 'FAILED FSM RESET'");
          }
         DATA_ERR_VAL("Severe Error occurred in opening the FS stream::"+string(exception.what()), -1);
         throw new TestFrameworkException("ParserManager::loadConfig["+string(exception.what())+"]");
     }
     DATA_INFO("Stream correctly loaded: next step may be implemented");
}

void ParserManager::parseConfig() throw (TestFrameworkException)
{
    ParserState* newState;
    ReturnCode retCode;
    try {
        newState = this->currentState->parse(loadedStream, tbParsed, &retCode);
        if(retCode.code == SUCCESS)
            DATA_INFO_VAL("Configuration correctly loaded: to be run test plan #", tbParsed->testPlanNr);
        else
            throw new TestFrameworkException(retCode.desc);
        delete this->currentState;
        this->currentState = newState;
    }catch(TestFrameworkException& exception)
     {
         /* failure management/recovery */
         try {
             this->currentState->error(&retCode);
             newState = this->currentState->reset(&retCode);
             delete this->currentState;
             this->currentState = newState;
         }catch(TestFrameworkException& exception) {
             DATA_ERR_VAL("Severe Error occurred in resetting the FSM::"+string(exception.what()), -1);
             throw new TestFrameworkException("ParserManager::loadConfig["+string(exception.what())+"] - 'FAILED FSM RESET'");
          }
         DATA_ERR_VAL("Severe Error occurred in parsing the FS stream::"+string(exception.what()), -1);
         throw new TestFrameworkException("ParserManager::parseConfig["+string(exception.what())+"]");
     }
     DATA_INFO("Configuration file correctly parsed: next step may be implemented");
}

ReturnCode ParserManager::validateConfig()
{
    ReturnCode retCode;
    ParserState* newState;
    try {
        newState = this->currentState->validate(tbParsed, &retCode);
        if(retCode.code == SUCCESS)
            DATA_INFO_VAL("Configuration correctly validated: to be run test plan #", tbParsed->testPlanNr);
        else
            throw new TestFrameworkException(retCode.desc);
        delete this->currentState;
        this->currentState = newState;
    }catch(TestFrameworkException& exception)
     {
         /* failure management/recovery */
         try {
             this->currentState->error(&retCode);
             newState = this->currentState->reset(&retCode);
             delete this->currentState;
             this->currentState = newState;
         }catch(TestFrameworkException& exception) {
             DATA_ERR_VAL("Severe Error occurred in resetting the FSM::"+string(exception.what()), -1);
             throw new TestFrameworkException("ParserManager::loadConfig["+string(exception.what())+"] - 'FAILED FSM RESET'");
          }
         DATA_ERR_VAL("Severe Error occurred in validating the FS stream::"+string(exception.what()), -1);
         throw new TestFrameworkException("ParserManager::validateConfig["+string(exception.what())+"]");
     }
    // TODO : create the testbench configuration object using the Loader
    //
    retCode.code = SUCCESS;
    retCode.desc = "Successfull Validation of the loaded Configuration File";
    DATA_INFO("Configuration File successfully validated");
    //
    return retCode;
}

ReturnCode ParserManager::init(const TestCaseLoader* loader)
{
    ReturnCode retCode;
    if(loader == 0) {
        retCode.code = ERROR;
        retCode.desc = "Null Pointer in Input for Test Case Loader";
        DATA_ERR_VAL("Null Pointer in Input for the instance of TestCaseLoader: Unable to proceed", loader);

        return retCode;
    }
    //
    if(this->currentState->isFSMInitialized()) {
        try {
            ParserState* newState = this->currentState->init(&retCode);     // FSM lazy initialization
            if(retCode.code == SUCCESS) {
                DATA_INFO("Parser Manager correctly registered the instance of Test Case Loader");
            }else {
                DATA_ERR_VAL("Runtime problem in initializing the FSM", -1);
                return retCode;
            }
            delete this->currentState;                                      // to avoid memory leaks
            this->currentState = newState;                                  // swap to new pointer
        }catch(TestFrameworkException& exception) {
            DATA_ERR_VAL("Severe Error occurred in initializing the FSM::"+string(exception.what()), -1);
            return retCode;
         }
    }
    //
    tcLoader = const_cast<TestCaseLoader*>(loader);
    retCode.code = SUCCESS;
    retCode.desc = "Test Case Loader correctly registered";
    DATA_INFO("Test Case Loader correctly registered");

    return retCode;
}

}   /* PARSER */
}   /* TESTBENCH */
}   /* IT */
