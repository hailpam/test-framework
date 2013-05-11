#include <fstream>
#include <rawlogger.h>
#include <debug.h>

using namespace std;
using namespace it::testbench::logger;

RawLogger* RawLogger::instance = 0; /*!< static pointer to ensure a single instance */
fstream RawLogger::fs;          /*!< File stream used for log file */
pthread_mutex_t RawLogger::logMux = PTHREAD_MUTEX_INITIALIZER;  /*!< mutex for protecting static variables */

RawLogger::RawLogger(){
    DEBUG("");
    /* Follow a lazy initialization strategy, do nothing here */
}

RawLogger::~RawLogger(){
    DEBUG("");
    /*  Close File stream if opened */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    if (fs.is_open())
        fs.close();
    pthread_mutex_unlock(&logMux);
}

RawLogger* RawLogger::getInstance(){
    DEBUG("");
    return instance;
}

RawLogger* RawLogger::getInstance(const string &logFile){
    DEBUG("");
    /* Lazy initialization */
    if (pthread_mutex_lock(&logMux) < 0)
        return 0;
    if (!instance && !fs.is_open()) {
        fs.open(logFile.c_str(), std::fstream::out);
        if (!fs.fail()) {
            instance = new RawLogger();
        }
    }
    pthread_mutex_unlock(&logMux);
    return instance;
}

void RawLogger::logT(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"T: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}

void RawLogger::logD(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"D: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}

void RawLogger::logI(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"I: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}

void RawLogger::logW(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"W: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}

void RawLogger::logE(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"E: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}

void RawLogger::logF(const string &str){
    DEBUG("");
    /* TODO: no concurrency control here!!! */
    /* TODO: get timestamp!!! */
    if (pthread_mutex_lock(&logMux) < 0)
        return;
    fs <<"F: " <<str.c_str() <<endl;
    fs.flush();
    pthread_mutex_unlock(&logMux);
}
