#include <fstream>

#include <RawLogger.h>
#include <debug.h>

using namespace std;

namespace it
{
namespace testbench
{
namespace logger
{

RawLogger::RawLogger(){
    /* Follow a late initialization strategy, just set 0 here */
    instance = 0;
}

RawLogger::~RawLogger(){
    /* If late initialization has been performed, then close file */
    if (fs.is_open())
        fs.close();
}

RawLogger::static RawLogger* getInstance(){
    return instance;
}

RawLogger::static RawLogger* getInstance(const char *logFile){
    /* Late initialization */
    if (!instance){
        instance = new RawLogger();
        if (!fs.is_open()){
            fs.open(logFile, out);
        }
    }
    return instance;
}

} /* LOGGER */
} /* TESTBENCH */
} /* IT */
