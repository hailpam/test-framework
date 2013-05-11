#include <concrete_testbuilder.h>

namespace it
{
namespace testbench
{
namespace data
{

/// TEST CASE BUILDER 1
TestCaseBuilder1::TestCaseBuilder1() {/* Do nothing */}
TestCaseBuilder1::~TestCaseBuilder1() {/* Do nothing */}
TestCase* TestCaseBuilder1::buildTestCase()
{
    /* dynamic initialization : to be deallocated outside */
    SetupTestItem* cSetItem = new CustomSetupItem();
    RunnableTestItem* cRunItem = new CustomRunnableTestItem();
    TearDownTestItem* ctdItem = new CustomTearDownTestItem();
    //
    TestCase* tCase = new TestCase();
    tCase->setTestCaseNumber(1);
    tCase->setSetupTestItem(cSetItem);
    tCase->setTearDownTestItem(ctdItem);
    tCase->addRunnableTestItem(cRunItem);
    cout << "[TestCaseBuilder1][TestCaseNr]["<< tCase->getTestCaseNumber() <<"]"<<endl;
    //
    return tCase;
}

/// TEST CASE BUILDER 2
TestCaseBuilder2::TestCaseBuilder2() {/* Do nothing */}
TestCaseBuilder2::~TestCaseBuilder2() {/* Do nothing */}
TestCase* TestCaseBuilder2::buildTestCase()
{
    /* dynamic initialization : to be deallocated outside */
    SetupTestItem* cSetItem = new CustomSetupItem();
    RunnableTestItem* cRunItem = new CustomRunnableTestItem();
    TearDownTestItem* ctdItem = new CustomTearDownTestItem();
    //
    TestCase* tCase = new TestCase();
    tCase->setTestCaseNumber(2);
    tCase->setSetupTestItem(cSetItem);
    tCase->setTearDownTestItem(ctdItem);
    tCase->addRunnableTestItem(cRunItem);
    cout << "[TestCaseBuilder2][TestCaseNr]["<< tCase->getTestCaseNumber() <<"]"<<endl;
    //
    return tCase;
}

/// TEST CASE BUILDER 3
TestCaseBuilder3::TestCaseBuilder3() {/* Do nothing */}
TestCaseBuilder3::~TestCaseBuilder3() {/* Do nothing */}
TestCase* TestCaseBuilder3::buildTestCase()
{
    /* dynamic initialization : to be deallocated outside */
    SetupTestItem* cSetItem = new CustomSetupItem();
    RunnableTestItem* cRunItem = new CustomRunnableTestItem();
    TearDownTestItem* ctdItem = new CustomTearDownTestItem();
    //
    TestCase* tCase = new TestCase();
    tCase->setTestCaseNumber(3);
    tCase->setSetupTestItem(cSetItem);
    tCase->setTearDownTestItem(ctdItem);
    tCase->addRunnableTestItem(cRunItem);
    cout << "[TestCaseBuilder3][TestCaseNr]["<< tCase->getTestCaseNumber() <<"]"<<endl;
    //
    return tCase;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
