#include <fstream>

#include <rawlogger.h>
#include <debug.h>

using namespace std;
using namespace it::testbench::logger;

RawLogger* RawLogger::instance = 0; /*!< static pointer to ensure a single instance */
fstream RawLogger::fs;          /*!< File stream used for log file */

RawLogger::RawLogger(){
    DEBUG("");
    /* Follow a lazy initialization strategy, do nothing here */
}

RawLogger::~RawLogger(){
    DEBUG("");
    /*  Close File stream if opened */
    if (fs.is_open())
        fs.close();
}

RawLogger* RawLogger::getInstance(){
    DEBUG("");
    return instance;
}

RawLogger* RawLogger::getInstance(const string logFile){
    DEBUG("");
    /* Lazy initialization */
    if (!instance && !fs.is_open()) {
        fs.open(logFile.c_str(), std::fstream::out);
        if (!fs.fail()) {
            instance = new RawLogger();
        }
    }
    return instance;
}

void RawLogger::logT(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"T: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logD(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"D: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logI(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"I: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logW(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"W: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logE(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"E: " <<str.c_str() <<endl;
    fs.flush();
}

void RawLogger::logF(const string str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    fs <<"F: " <<str.c_str() <<endl;
    fs.flush();
}
