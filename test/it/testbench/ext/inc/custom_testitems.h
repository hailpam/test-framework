#ifndef CUSTOM_TESTITEMS_H
#define CUSTOM_TESTITEMS_H

#include <testitem.h>

#include <concrete_ctxobject.h>

namespace it
{
namespace testbench
{
namespace data
{

class CustomSetupItem : public SetupTestItem {
    public:
//        CustomSetupItem();
        TestCaseContext* setupItem();
};

class CustomRunnableTestItem : public RunnableTestItem {
    public:
//        CustomRunnableTestItem();
        ReturnCode* runItem(TestCaseContext* ctxObject);
};

class CustomTearDownTestItem : public TearDownTestItem {
    public:
//        CustomTearDownTestItem ();
        void tearDownItem(TestCaseContext* ctxObject);
};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* CUSTOM_TESTITEMS_H */
