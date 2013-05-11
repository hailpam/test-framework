#include <support.h>

namespace it
{
namespace testbench
{
namespace data
{


TestFrameworkException::TestFrameworkException(string msg)  throw() {errMsg = msg;}
TestFrameworkException::~TestFrameworkException() throw() {}

const char* TestFrameworkException::what() const throw() {return errMsg.c_str();}

} /* DATA */
} /* TESTBENCH */
} /* IT */
