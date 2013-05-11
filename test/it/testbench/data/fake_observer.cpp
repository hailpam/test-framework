#include <fake_observer.h>

#include <iostream>

namespace it
{
namespace testbench
{
namespace data
{

FakeObserver::FakeObserver()
{
    Observer::whoAmI = "FakeObserver";
}

FakeObserver::~FakeObserver() {/* Do nothing */}

void FakeObserver::notify(Report* report)
{
    DATA_INFO_VAL("Notified the Fake Observer, Report in Session",report->getTestPlanId());
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
