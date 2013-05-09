#include <testbench.h>

namespace it
{
namespace testbench
{
namespace data
{

/// TEST BENCH CONFIGURATION

TestBenchConfiguration::TestBenchConfiguration() {}
TestBenchConfiguration::~TestBenchConfiguration() {}

void TestBenchConfiguration::setSessionId(const string* sId)
{
}

const string* TestBenchConfiguration::getSessionId()
{
    return 0;
}

void TestBenchConfiguration::addRange(const string* tPlanId, const Range* range)
{
}

const Range* TestBenchConfiguration::retrieveRange(const string* tPlanId)
{
    return 0;
}

void TestBenchConfiguration::setSupporterFormat(SupportedFormats format)
{
}

SupportedFormats TestBenchConfiguration::getSupportedFormat()
{
    return CSV;
}

void TestBenchConfiguration::setNrOfThreads(int threadNo)
{
}

int TestBenchConfiguration::getNrOfThreads()
{
    return 0;
}

void TestBenchConfiguration::addTestPlan(const string* tPlanId, const TestPlan* tPlan)
{
}

const TestPlan* TestBenchConfiguration::retrieveTestPlan(const string* tPlanId)
{
    return 0;
}

/// TEST PLAN

TestPlan::TestPlan() {}
TestPlan::~TestPlan() {}

void TestPlan::addTestCase(int tcIdx, const TestCase* tCase) {}
const TestCase* TestPlan::retrieveTestCase(int tcIdx) {return 0;}
bool TestPlan::removeTestCase(int tcIdx) {return true;}
bool TestPlan::updateTestCase(int tcIdx, const TestCase* tCase) {return true;}

/// TEST CASE

TestCase::~TestCase() {}
bool TestCase::setupTestCase() {return true;}
bool TestCase::runTestCase() {return true;}
bool TestCase::tearDownTestCase() {return true;}
void TestCase::setSetupTestItem(const SetupTestItem* sTestItem) {}
void TestCase::setTearDownTestItem(const TearDownTestItem* tdTestItem) {}
void TestCase::setTestCaseContextObject(const TestCaseContext* tcCtxObject) {}
void TestCase::addRunnableTestItem(const RunnableTestItem* rTestItem) {}
void TestCase::addReport(const Report* report) {}

} /* DATA */
} /* TESTBENCH */
} /* IT */
