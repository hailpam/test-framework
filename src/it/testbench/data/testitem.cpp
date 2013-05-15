#include <testitem.h>

namespace it
{
namespace testbench
{
namespace data
{

/// SETUP TEST ITEM

ReturnCode* SetupTestItem::runItem(TestCaseContext* ctxObject) { return 0; }

void SetupTestItem::tearDownItem(TestCaseContext* ctxObject) {}

/// RUNNABLE TEST ITEM

TestCaseContext* RunnableTestItem::setupItem() { return 0; }

void RunnableTestItem::tearDownItem(TestCaseContext* ctxObject) {}

/// TEARDOWN TEST ITEM

TestCaseContext* TearDownTestItem::setupItem() { return 0; }

ReturnCode* TearDownTestItem::runItem(TestCaseContext* ctxObject) { return 0; }

} /* DATA */
} /* TESTBENCH */
} /* IT */
