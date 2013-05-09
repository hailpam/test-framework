#include <observer.h>

namespace it
{
namespace testbench
{
namespace data
{

class FakeObserver : public Observer {
    public:
        FakeObserver();
        ~FakeObserver();
        void notify(const Report* report);
};

} /* DATA */
} /* TESTBENCH */
} /* IT */
