#include <fstream>

#include <rawlogger.h>
#include <debug.h>

using namespace std;

namespace it
{
namespace testbench
{
namespace logger
{

RawLogger::RawLogger(){
    /* Follow a lazy initialization strategy, just set 0 here */
    instance = 0;
}

RawLogger::~RawLogger(){
    /*  Close File stream if opened */
    if (fs.is_open())
        fs.close();
}

RawLogger* RawLogger::getInstance(){
    return instance;
}

RawLogger* RawLogger::getInstance(const string logFile){
    /* Lazy initialization */
    if (!instance){
        instance = new RawLogger();
        if (!fs.is_open())
            fs.open(logFile.c_str(), std::fstream::out);
    }
    return instance;
}

void RawLogger::logT(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"T: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logD(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"D: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logI(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"I: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logW(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"W: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logE(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"E: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logF(const string str){
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"F: " <<str.c_str() <<endl;
    fs.flush();
}

} /* LOGGER */
} /* TESTBENCH */
} /* IT */
