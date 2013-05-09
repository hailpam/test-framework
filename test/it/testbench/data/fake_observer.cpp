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
    whoAmI = new  string("");
}

FakeObserver::~FakeObserver()
{
    delete whoAmI;
}

void FakeObserver::notify(const Report* report) {
    cout << "FakeObserver::notify::whoAmI ["<< *whoAmI <<"]"<< endl;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
