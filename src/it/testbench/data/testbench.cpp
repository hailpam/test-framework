#include <testbench.h>

namespace it
{
namespace testbench
{
namespace data
{

/// TEST BENCH CONFIGURATION

TestBenchConfiguration::TestBenchConfiguration()
{
    nrOfThreads = NR_OF_THREADS;
}

TestBenchConfiguration::~TestBenchConfiguration()
{
    // TODO deallocate vector of Ranges
}

ReturnCode TestBenchConfiguration::setSessionId(const string& sId)
{
    ReturnCode retCode;
    if(sId.length() == 0) {
        DATA_ERR_VAL("Blank string in Input#", sId);
        retCode.code = ERROR;
        retCode.desc = "BLANK string in Input";

        return retCode;
    }
    sessionId = sId;
    retCode.code = SUCCESS;
    retCode.desc = "String Session Id correctly Set";
    DATA_INFO_VAL("Session Id has been correclty set to#", sId);

    return retCode;
}

const string* TestBenchConfiguration::getSessionId() const
{
    return &sessionId;
}

ReturnCode TestBenchConfiguration::addRange(const string& tPlanId, const Range& range)
{
    ReturnCode retCode;
    if(tPlanId.length() == 0) {
        DATA_ERR_VAL("Blank string in Input#", tPlanId);
        retCode.code = ERROR;
        retCode.desc = "BLANK string in Input";

        return retCode;
    }
    if(range.from == 0 && range.to == 0) {
        DATA_ERR_VAL("Invalid Range, both indexes are#", 0);
        retCode.code = ERROR;
        retCode.desc = "Both indexes in the Range are 0";

        return retCode;
    }
    Range* ptrToRange = new Range;
    ptrToRange->from = range.from;
    ptrToRange->to = range.to;
    tcToBeExecuted[tPlanId] = ptrToRange;
    //
    retCode.code = SUCCESS;
    retCode.desc = "Range correclty loaded";
    DATA_INFO("Range Correclty Loaded");

    return retCode;
}

const Range* TestBenchConfiguration::retrieveRange(const string* tPlanId)
{
    if(tPlanId == 0) {
        DATA_ERR_VAL("NULL Pointer in Input", tPlanId);

        return 0;
    }
    if((*tPlanId).size() == 0) {
        DATA_ERR_VAL("BLANK String (Test Plan Id) in Input", tPlanId);

        return 0;
    }
    string* tmpPtr = const_cast<string*>(tPlanId);

    return tcToBeExecuted[*tmpPtr];
}

void TestBenchConfiguration::setSupporterFormat(SupportedFormats format)
{
    this->format = format;
}

SupportedFormats TestBenchConfiguration::getSupportedFormat()
{
    return format;
}

void TestBenchConfiguration::setNrOfThreads(unsigned int threadNo)
{
    nrOfThreads = threadNo;
}

unsigned int TestBenchConfiguration::getNrOfThreads()
{
    return nrOfThreads;
}

ReturnCode TestBenchConfiguration::addTestPlan(const string* tPlanId, TestPlan* tPlan)
{
    ReturnCode retCode;
    if(tPlanId == 0) {
        DATA_ERR_VAL("NULL Pointer in Input as Test Plan Id", tPlanId);
        retCode.code = ERROR;
        retCode.desc = "NULL Pointer in Input as Test Plan Id";

        return retCode;
    }
    if((*tPlanId).size() == 0) {
        DATA_ERR_VAL("BLANK String in Input as Test Plan Id", *tPlanId);
        retCode.code = ERROR;
        retCode.desc = "BLANK String in Input as Test Plan Id";

        return retCode;
    }
    if(tPlan == 0) {
        DATA_ERR_VAL("NULL Pointer in Input as Test Plan", tPlan);
        retCode.code = ERROR;
        retCode.desc = "NULL Pointer in Input as Test Plan";

        return retCode;
    }
    pTestPlan[*tPlanId] = tPlan;
    tPlan->setParent(this);
    tPlan->setTestPlanId(*tPlanId);
    //
    retCode.code = SUCCESS;
    retCode.desc = "Test Plan added Successfully";
    DATA_INFO("Test Plan added Successfully");
    //
    return retCode;
}

const TestPlan* TestBenchConfiguration::retrieveTestPlan(const string* tPlanId)
{
    if(tPlanId == 0) {
        DATA_ERR_VAL("BLANK String in Input as Test Plan Id", *tPlanId);

        return 0;
    }
    string* tmpPtr = const_cast<string*>(tPlanId);

    return pTestPlan[*tmpPtr];
}

/// TEST PLAN

TestPlan::TestPlan()
{
    parent = 0;
}

TestPlan::~TestPlan() {/* Do nothing */}

void TestPlan::setParent(const TestBenchConfiguration* parent)
{
    this->parent = parent;
}

ReturnCode TestPlan::setTestPlanId(const string& tId)
{
    ReturnCode retCode;
    if (tId.size() == 0) {
        retCode.code = ERROR;
        retCode.desc = "Invalid Test Plan Id";
    } else {
        testPlanId = tId;
        retCode.code = SUCCESS;
        retCode.desc = "Test Plan Id set successfully";
    }
    return retCode;
}

const string* TestPlan::getTestPlanId() const
{
    return &testPlanId;
}

const string* TestPlan::getSessionId() const
{
    return parent->getSessionId();
}

ReturnCode TestPlan::addTestCase(unsigned int tcIdx, TestCase* tCase)
{
    ReturnCode retCode;
    if(tCase == 0) {
        //DATA_ERR_VAL("NULL Pointer for the Test Case", tCase);
        retCode.code = ERROR;
        retCode.desc = "NULL Pointer to the Test Case";

        return retCode;
    }
    if(listOfTests.size() == 0)
        listOfTests.reserve((tcIdx + 10));
    itrList = listOfTests.begin();
    std::advance(itrList,tcIdx);
    listOfTests.insert(itrList, const_cast<TestCase*>(tCase));
    tCase->setParent(this);
    tCase->setTestCaseNumber(tcIdx);
    DATA_INFO_VAL("Test Case added successfully, current Count#", listOfTests.size());
    //
    retCode.code = SUCCESS;
    retCode.desc = "Test Case added Successfully";
    //
    return retCode;
}

const TestCase* TestPlan::retrieveTestCase(unsigned int tcIdx) const
{
    if(tcIdx > listOfTests.size()) {
        //DATA_ERR_VAL("Povided Index is out of bound, current Count#", listOfTests.size());

        return 0;
    }
    TestCase* tmp = listOfTests.at(tcIdx);
    DATA_INFO_VAL("Test Case retrievable successfully, Number#", tmp->getTestCaseNumber());
    //
    return tmp;
}

ReturnCode TestPlan::removeTestCase(unsigned int tcIdx)
{
    ReturnCode retCode;
    if(tcIdx > listOfTests.size()) {
        //DATA_ERR_VAL("Povided Index is out of bound, current Count#", listOfTests.size());
        retCode.code = ERROR;
        retCode.desc = "Provided and Index that is currently Out of Bounds";

        return retCode;
    }
    itrList = listOfTests.begin();
    std::advance(itrList,tcIdx);
    listOfTests.erase(itrList);
    //
    retCode.code = SUCCESS;
    retCode.desc = "Test Case removed Successfully";
    DATA_INFO_VAL("Test Case removed successfully, current Count#", listOfTests.size());
    //
    return retCode;
}

ReturnCode TestPlan::updateTestCase(unsigned int tcIdx, const TestCase* tCase)
{
    ReturnCode retCode;
    if(tcIdx > listOfTests.size()) {
        //DATA_ERR_VAL("Povided Index is out of bound, current Count#", listOfTests.size());
        retCode.code = ERROR;
        retCode.desc = "Provided and Index that is currently Out of Bounds";

        return retCode;
    }
    listOfTests[tcIdx] = const_cast<TestCase*>(tCase);
    //
    retCode.code = SUCCESS;
    retCode.desc = "Test Case removed Successfully";
    DATA_INFO_VAL("Test Case updated successfully, current Test#", tcIdx);
    //
    return retCode;
}

const unsigned int TestPlan::getNrOfTestCases()
{
    return listOfTests.size();
}

/// TEST CASE
TestCase::TestCase()
{
    parent = 0;
    sTestItem = 0;
    tdTestItem = 0;
    ctxObject = 0;
}

TestCase::~TestCase()
{
    /* dynamically created outside: they die with their container (TC) */
    delete sTestItem;
    delete tdTestItem;
    // deallocate runnable test items
    list<RunnableTestItem*>::iterator itrList;
    for(itrList = rTestItems.begin(); itrList != rTestItems.end(); ++itrList) {
        delete *itrList;
    }
    // deallocate the reports
    list<ReturnCode*>::iterator itrRetCode;
    for(itrRetCode = tcRetcodes.begin(); itrRetCode != tcRetcodes.end(); ++itrRetCode) {
        delete *itrRetCode;
    }
}

Report* TestCase::finalizeReport() {
    Report *report = new Report();
    const string *sessionId = parent->getSessionId();
    report->setSessionId(sessionId);
    const string *testPlanId = parent->getTestPlanId();
    report->setTestPlanId(testPlanId);
    report->setTestId(tcNumber);
    report->setOutcome(&tcRetcodes);
    return report;
}

void TestCase::setParent(const TestPlan* parent)
{
    this->parent = parent;
}

void TestCase::setupTestCase() throw(TestFrameworkException)
{
    if(this->sTestItem == 0) {
        //DATA_ERR_VAL("NULL Pointer for Setup Test item", sTestItem);
        throw new TestFrameworkException("Uninitialized Setup Test Item: Unable to proceed");
    }
    this->ctxObject = this->sTestItem->setupItem();
    if(this->ctxObject == 0) {
        //DATA_ERR_VAL("NULL Pointer for Context Object", ctxObject);
        throw new TestFrameworkException("Uninitialized Context Object: Unable to proceed");
    }
    DATA_INFO("Setup successfully implemented!");
}

void TestCase::runTestCase() throw(TestFrameworkException)
{
    if(this->ctxObject == 0) {
        //DATA_ERR_VAL("NULL Pointer for Context Object", ctxObject);
        throw new TestFrameworkException("Uninitialized Context Object: Unable to proceed");
    }
    list<RunnableTestItem*>::iterator itrList;
    for(itrList = rTestItems.begin(); itrList != rTestItems.end(); ++itrList) {
        ReturnCode* ptrRetCode = (*itrList)->runItem(this->ctxObject);
        if(ptrRetCode  == 0) {
            /* recovery action is needed: don't trust */
            //DATA_ERR_VAL("Report not generated for Item#", distance(rTestItems.begin(),itrList));
            continue;
        }
        tcRetcodes.push_back(ptrRetCode);
    }
    DATA_INFO("Run successfully implemented!");
    DATA_INFO_VAL("Test ReturnCode Count", tcRetcodes.size());
}

void TestCase::tearDownTestCase() throw(TestFrameworkException)
{
    if(this->tdTestItem == 0) {
        //DATA_ERR_VAL("NULL Pointer for Tear Down Test Item", this->tdTestItem);
        throw new TestFrameworkException("Uninitialized Tear Down Test Item: Unable to proceed");
    }
    /* DANGEREOUS :: Likely memory leak */
    if(this->ctxObject == 0) {
        //DATA_ERR_VAL("NULL Pointer for Context Object", ctxObject);
        throw new TestFrameworkException("Uninitialized Context Object: Unable to proceed");
    }
    this->tdTestItem->tearDownItem(this->ctxObject);
    DATA_INFO("Tear Down successfully implemented!");
}

void TestCase::setSetupTestItem(const SetupTestItem* sTestItem)
{
    this->sTestItem = const_cast<SetupTestItem*>(sTestItem);
    DATA_INFO_VAL("Setup Test Item association accomplished", this->sTestItem);
}

void TestCase::setTearDownTestItem(const TearDownTestItem* tdTestItem)
{
    this->tdTestItem = const_cast<TearDownTestItem*>(tdTestItem);
    DATA_INFO_VAL("Teard Down Item association accomplished", this->tdTestItem);
}

void TestCase::setTestCaseContextObject(const TestCaseContext* tcCtxObject)
{
    this->ctxObject = const_cast<TestCaseContext*>(tcCtxObject);
    DATA_INFO_VAL("Context Object association accomplished", this->ctxObject);
}

void TestCase::addRunnableTestItem(const RunnableTestItem* rTestItem)
{
    rTestItems.push_back(const_cast<RunnableTestItem*>(rTestItem));
    DATA_INFO_VAL("Added Runnable Test Item ", rTestItem);
}

void TestCase::addReturnCode(const ReturnCode* retCode)
{
    tcRetcodes.push_back(const_cast<ReturnCode*>(retCode));
    DATA_INFO_VAL("Added ReturnCode successfully", retCode);
}

void TestCase::setTestCaseNumber(const unsigned int tcNo)
{
    tcNumber = tcNo;
}

const unsigned int TestCase::getTestCaseNumber() const
{
    return tcNumber;
}

/// TEST CASE LOADER

TestCaseLoader::TestCaseLoader() {/* Do nothing */}

TestCaseLoader::~TestCaseLoader() {/* Do nothing */}

ReturnCode TestCaseLoader::loadTestCase(unsigned int tcIdx)
{
    // TODO : to be reviewed : segmentation fault without the initial PAD
    ReturnCode retCode;
    if(tcList.size() == 0) {
        tcList.reserve((tcIdx + 10));
        TestCase* pad = new TestCase();
        pad->setTestCaseNumber(100000);
        pad->setSetupTestItem(0);
        pad->setTearDownTestItem(0);
        pad->addRunnableTestItem(0);
        tcList.push_back(pad);
    }
    if(tcIdx > tcBuilders.size()) {
        DATA_INFO("Index Out of Bound :: Operation Failed");
        retCode.code = ERROR;
        retCode.desc = "Index Out of Bound :: Operation Failed";

        return retCode;
    }
    TestCaseBuilder* tcBuild = tcBuilders[tcIdx];
    TestCase* ptrToTC = tcBuild->buildTestCase();
    DATA_INFO("Test Case built successfully");
    itrList = tcList.begin();
    std::advance(itrList,tcIdx);
    tcList.insert(itrList, ptrToTC);
    DATA_INFO("Test Case inserted successfully");
    retCode.code = SUCCESS;
    retCode.desc = "Test Case loaded";

    return retCode;
}

ReturnCode TestCaseLoader::loadAllTestCases()
{
    ReturnCode retCode;
    if(tcList.size() == 0)
        tcList.reserve(20);
    if(tcBuilders.size() == 0) {
        DATA_INFO("No Test Case Builder Registered :: Operation Failed");
        retCode.code = ERROR;
        retCode.desc = "No Test Case Builder Registered :: Operation Failed";

        return retCode;
    }
    vector<TestCaseBuilder*>::iterator itrVector;
    for(itrVector = tcBuilders.begin(); itrVector != tcBuilders.end(); ++itrVector) {
        TestCase* ptrToTC = (*itrVector)->buildTestCase();
        DATA_INFO("Test Case built successfully");
        int idx = (int)(ptrToTC->getTestCaseNumber());
        itrList = tcList.begin();
        std::advance(itrList,idx);
        tcList.insert(itrList, ptrToTC);
        DATA_INFO("Test Case inserted successfully");
    }
    retCode.code = SUCCESS;
    retCode.desc = "All Test Cases loaded";

    return retCode;
}

const TestCase* TestCaseLoader::getLoadedTestCase(unsigned int tcIdx) const
{
    if(tcIdx > tcList.size()) {
        DATA_INFO("Index Out of Bound :: Operation Failed");

        return 0;
    }
    if(tcList.size() == 0) {
        DATA_INFO("No Test Cases Loaded:: Operation Failed");

        return 0;
    }
    TestCase* tmpPtr = tcList[tcIdx];
    if(tmpPtr != 0)
        DATA_INFO_VAL("Retrieved the Test Case#", tmpPtr->getTestCaseNumber());
    else
        DATA_ERR_VAL("Retrieved a NULL Pointer::BE CAREFUL", tmpPtr);

    return tmpPtr;
}

const vector<TestCase*>* TestCaseLoader::getAllLoadedTestCases() const
{
    return &tcList;
}

ReturnCode TestCaseLoader::registerTestCaseBuilder(unsigned const int tcIdx, const TestCaseBuilder* tcBuilder)
{
    ReturnCode retCode;
    if(tcBuilders.size() == 0)
        tcBuilders.reserve((tcIdx + 10));
    itrBuildList = tcBuilders.begin();
    std::advance(itrBuildList, tcIdx);
    tcBuilders.insert(itrBuildList, const_cast<TestCaseBuilder*>(tcBuilder));
    retCode.code = SUCCESS;
    retCode.desc = "Test Case Builder registered";
    DATA_INFO_VAL("Test Case Builder has been correctly inserted, at#", tcIdx);

    return retCode;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
