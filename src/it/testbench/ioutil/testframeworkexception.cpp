#include <fsmanager.h>

namespace it
{
namespace testbench
{
namespace ioutil
{


TestFrameworkException::TestFrameworkException(string msg)  throw() {errMsg = msg;}
TestFrameworkException::~TestFrameworkException() throw() {}

const char* TestFrameworkException::what() const throw() {return errMsg.c_str();}

} /* IOUTIL */
} /* TESTBENCH */
} /* IT */
