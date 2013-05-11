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

TestBenchConfiguration::~TestBenchConfiguration() {/* Do notghing */}

void TestBenchConfiguration::setSessionId(const string* sId)
{
    if(sId == 0) {
        DEBUG("TestBenchConfiguration::setSessionId Uninitialized Pointer as Session Id in Input :: Operation Failed");
    }
    this->sessionId = const_cast<string*>(sId);
}

const string* TestBenchConfiguration::getSessionId() const
{
    return this->sessionId;
}

void TestBenchConfiguration::addRange(const string* tPlanId, const Range* range)
{
    if(tPlanId == 0) {
        DEBUG("TestBenchConfiguration::addRange Uninitialized Pointer as Test Plan Id :: Operation Failed");
    }
    if(range == 0) {
        DEBUG("TestBenchConfiguration::addRange Uninitialized Pointer as Range :: Operation Failed");
    }
    tcToBeExecuted[*tPlanId] = const_cast<Range*>(range);
}

const Range* TestBenchConfiguration::retrieveRange(const string* tPlanId)
{
    if(tPlanId == 0) {
        DEBUG("TestBenchConfiguration::retrieveRange Uninitialized Pointer as Test Plan Id :: Operation Failed");
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

int TestBenchConfiguration::getNrOfThreads()
{
    return nrOfThreads;
}

void TestBenchConfiguration::addTestPlan(const string* tPlanId, const TestPlan* tPlan)
{
    if(tPlanId == 0) {
        DEBUG("TestBenchConfiguration::addTestPlan Uninitialized Pointer as Test Plan Id :: Operation Failed");
    }
    if(tPlan == 0) {
        DEBUG("TestBenchConfiguration::addTestPlan Uninitialized Pointer as Test Plan :: Operation Failed");
    }
    pTestPlan[*tPlanId] = const_cast<TestPlan*>(tPlan);
}

const TestPlan* TestBenchConfiguration::retrieveTestPlan(const string* tPlanId)
{
    if(tPlanId == 0) {
        DEBUG("TestBenchConfiguration::retrieveTestPlan Uninitialized Pointer as Test Plan Id :: Operation Failed");
    }
    string* tmpPtr = const_cast<string*>(tPlanId);

    return pTestPlan[*tmpPtr];
}

/// TEST PLAN

TestPlan::TestPlan() {/* Do nothing */}
TestPlan::~TestPlan() {/* Do nothing */}

void TestPlan::addTestCase(unsigned int tcIdx, const TestCase* tCase)
{
    // TODO : this doesn't work well : the size increases not normally
    if(tCase == 0) {
        DEBUG("TestPlan::addTestCase Uninitialized Pointer to Test Case in Input :: Operation Failed");
        return;
    }
    if(listOfTests.size() == 0)
        listOfTests.reserve((tcIdx + 10));
    itrList = listOfTests.begin();
    std::advance(itrList,tcIdx);
    listOfTests.insert(itrList, const_cast<TestCase*>(tCase));
    strStream << listOfTests.size();
    DATA_INFO_VAL("Numer of Test in the Set", listOfTests.size());
    strStream.str("");
}

const TestCase* TestPlan::retrieveTestCase(unsigned int tcIdx) const
{
    if(tcIdx > listOfTests.size()) {
        DEBUG("TestPlan::retrieveTestCase Index Out of Bound :: Operation Failed");
        return 0;
    }
    return listOfTests.at(tcIdx);;
}

bool TestPlan::removeTestCase(unsigned int tcIdx)
{
    if(tcIdx > listOfTests.size()) {
        DEBUG("TestPlan::removeTestCase Index Out of Bound :: Operation Failed");
        return false;
    }
    itrList = listOfTests.begin();
    std::advance(itrList,tcIdx);
    listOfTests.erase(itrList);

    return true;
}

bool TestPlan::updateTestCase(unsigned int tcIdx, const TestCase* tCase)
{
    if(tcIdx > listOfTests.size()) {
        DEBUG("TestPlan::updateTestCase Index Out of Bound :: Operation Failed");
        return false;
    }
    listOfTests[tcIdx] = const_cast<TestCase*>(tCase);

    return true;
}

const int TestPlan::getNrOfTestCases()
{
    return listOfTests.size();
}

/// TEST CASE
TestCase::TestCase() {/* Do nothing */}

TestCase::~TestCase()
{
    /* dynamically created outside: they die with their container (TC) */
    delete sTestItem;
    delete tdTestItem;
    delete ctxObject;
}

bool TestCase::setupTestCase()
{
    if(this->sTestItem == 0) {
        DEBUG("TestCase::setupTestCase:: Uninitialized Pointer to Test Item");
        return false;
    }
    this->ctxObject = this->sTestItem->setupItem();
    if(this->ctxObject == 0) {
        DEBUG("TestCase::setupTestCase:: Returned Uninitialized Pointer to Ctx Object");
        return false;
    }
    return true;
}

bool TestCase::runTestCase()
{
    if(this->ctxObject == 0) {
        DEBUG("TestCase::setupTestCase:: Using Uninitialized Pointer to Ctx Object");
        return false;
    }
    list<RunnableTestItem*>::iterator itrList;
    for(itrList = rTestItems.begin(); itrList != rTestItems.end(); ++itrList) {
        Report* ptrReport = (*itrList)->runItem(this->ctxObject);
        if(ptrReport  == 0) {
            /* recovery action is needed: don't trust */
            DEBUG("TestCase::setupTestCase:: Returned Uninitialized Pointer to Report");
            continue;
        }
        tcReports.push_back(ptrReport);
    }
    return true;
}

bool TestCase::tearDownTestCase()
{
    if(this->tdTestItem == 0) {
        DEBUG("TestCase::tearDownTestCase Uninitialized Pointer to Test Item");
        return false;
    }
    /* DANGEREOUS :: Likely memory leak */
    if(this->ctxObject == 0) {
        DEBUG("TestCase::tearDownTestCase:: Using Uninitialized Pointer to Ctx Object");
        return false;
    }
    this->tdTestItem->tearDownItem(this->ctxObject);
    return true;
}

void TestCase::setSetupTestItem(const SetupTestItem* sTestItem)
{
    this->sTestItem = const_cast<SetupTestItem*>(sTestItem);
    strStream << this->sTestItem;
    DEBUG("TestCase::setSetupTestItem::Pointer Set ["+strStream.str()+"]");
    strStream.str("");
}

void TestCase::setTearDownTestItem(const TearDownTestItem* tdTestItem)
{
    this->tdTestItem = const_cast<TearDownTestItem*>(tdTestItem);
    strStream << this->tdTestItem;
    DEBUG("TestCase::setTearDownTestItem::Pointer Set ["+strStream.str()+"]");
    strStream.str("");
}

void TestCase::setTestCaseContextObject(const TestCaseContext* tcCtxObject)
{
    this->ctxObject = const_cast<TestCaseContext*>(tcCtxObject);
    strStream << this->ctxObject;
    DEBUG("TestCase::setTestCaseContextObject::Pointer Set ["+strStream.str()+"]");
    strStream.str("");
}

void TestCase::addRunnableTestItem(const RunnableTestItem* rTestItem)
{
    rTestItems.push_back(const_cast<RunnableTestItem*>(rTestItem));
    strStream << rTestItems.size();
    DEBUG("TestCase::addRunnableTestItem Runnable Item ["+strStream.str()+"]");
    strStream.str("");
}

void TestCase::addReport(const Report* report)
{
    tcReports.push_back(const_cast<Report*>(report));
#ifdef DEBUG_PRINT_ENABLED
    strStream << tcReports.size();
    DEBUG("TestCase::addRunnableTestItem Report ["+strStream.str()+"]");
    strStream.str("");
#endif
}

void TestCase::setTestCaseNumber(const unsigned int& tcNo)
{
    tcNumber = tcNo;
}

const int TestCase::getTestCaseNumber() const
{
    return tcNumber;
}

/// TEST CASE LOADER

TestCaseLoader::TestCaseLoader() {/* Do nothing */}

TestCaseLoader::~TestCaseLoader() {/* Do nothing */}

bool TestCaseLoader::loadTestCase(unsigned int tcIdx)
{
    if(tcList.size() == 0) {
        tcList.reserve((tcIdx + 10));
        TestCase* pad = new TestCase();
        pad->setTestCaseNumber(100000);
        pad->setSetupTestItem(0);
        pad->setTearDownTestItem(0);
        pad->addRunnableTestItem(0);
        cout <<"chitammuort!";
        tcList.push_back(pad);
    }
    if(tcIdx > tcBuilders.size()) {
        DEBUG("TestCaseLoader::loadTestCase Index Out of Bound :: Operation Failed");
        return false;
    }
    TestCaseBuilder* tcBuild = tcBuilders[tcIdx];
    TestCase* ptrToTC = tcBuild->buildTestCase();
    DEBUG("TestCaseLoader::loadTestCase Test Case built successfully");
    itrList = tcList.begin();
    cout << 1;
    std::advance(itrList,tcIdx);
    cout << 2;
    tcList.insert(itrList, ptrToTC);
    cout << 3;
    DEBUG("TestCaseLoader::loadTestCase Test Case inserted successfully");

    return true;
}

bool TestCaseLoader::loadAllTestCases()
{
    if(tcList.size() == 0)
        tcList.reserve(20);
    if(tcBuilders.size() == 0) {
        DEBUG("TestCaseLoader::loadAllTestCases No Test Case Builder Registered :: Operation Failed");
        return false;
    }
    vector<TestCaseBuilder*>::iterator itrVector;
    for(itrVector = tcBuilders.begin(); itrVector != tcBuilders.end(); ++itrVector) {
        TestCase* ptrToTC = (*itrVector)->buildTestCase();
        DEBUG("TestCaseLoader::loadAllTestCases Test Case built successfully");
        int idx = (int)(ptrToTC->getTestCaseNumber());
        itrList = tcList.begin();
        std::advance(itrList,idx);
        tcList.insert(itrList, ptrToTC);
        DEBUG("TestCaseLoader::loadTestCase Test Case inserted successfully");
    }

    return true;
}

const TestCase* TestCaseLoader::getLoadedTestCase(unsigned int tcIdx) const
{
    if(tcIdx > tcList.size()) {
        DEBUG("TestCaseLoader::getLoadedTestCase Index Out of Bound :: Operation Failed");
        return 0;
    }
    if(tcList.size() == 0) {
        DEBUG("TestCaseLoader::getLoadedTestCase No Test Cases Loaded:: Operation Failed");
        return 0;
    }
    DATA_INFO_VAL("Test Case Id", 1000000);
    return tcList[tcIdx];
}

const vector<TestCase*>* TestCaseLoader::getAllLoadedTestCases() const
{
    return &tcList;
}

bool TestCaseLoader::registerTestCaseBuilder(unsigned const int tcIdx, const TestCaseBuilder* tcBuilder)
{
    if(tcBuilders.size() == 0)
        tcBuilders.reserve((tcIdx + 10));
    itrBuildList = tcBuilders.begin();
    std::advance(itrBuildList, tcIdx);
    tcBuilders.insert(itrBuildList, const_cast<TestCaseBuilder*>(tcBuilder));

    return true;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
