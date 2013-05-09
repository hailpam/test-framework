#include <fstream>

#include <rawlogger.h>
#include <debug.h>

using namespace std;
using namespace it::testbench::logger;

RawLogger* RawLogger::instance = 0; /*!< static pointer to ensure a single instance */
fstream RawLogger::fs;          /*!< File stream used for log file */

RawLogger::RawLogger(){
    /* Follow a lazy initialization strategy, do nothing here */
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
    if (!instance && !fs.is_open()) {
        fs.open(logFile.c_str(), std::fstream::out);
        if (!fs.fail()) {
            instance = new RawLogger();
        }
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
