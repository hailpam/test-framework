#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// $Id$
/**
 * @file Logger.h
 * Logging functionality for the test-framework system.
 *
 * @author Raffaele Aquilone <aquiloneraf@gmail.com>
 * @version 0.1
 */
// $Log$

using namespace std;

namespace it
{
namespace testbench
{
namespace logger
{

/**
 * Abstract global Logger.
 */
class Logger {
    private:
        static Logger *instance; /** static pointer to ensure a single instance */
        /**
         * Virtual, so that it can't be called explicitly. Logging service
         * initialization is done at configuration time when a log file path
         * and name is passed.
         */
        virtual Logger();
        /**
         * Virtual, so that it can't be called explicitly. Tear down the Logging
         * service at system shutdown.
         */
        virtual ~Logger();

    public:
        /**
         * Return unique instance
         */
        virtual static Logger* getInstance() = 0;
        /**
         * Return unique instance and open Log file
         * @param[in] logFile Log file pathname
         */
        virtual static Logger* getInstance(const char* logFile) = 0;
        /**
         * Trace level logging
         * @param[in] s Log message
         */
        virtual void logT(const string s) = 0;
        /**
         * Debug level logging
         * @param[in] s Log message
         */
        virtual void logD(const string s) = 0;
        /**
         * Information level logging
         * @param[in] s Log message
         */
        virtual void logI(const string s) = 0;
        /**
         * Warning level logging
         * @param[in] s Log message
         */
        virtual void logW(const string s) = 0;
        /**
         * Error level logging
         * @param[in] s Log message
         */
        virtual void logE(const string s) = 0;
        /**
         * Fatal level logging
         * @param[in] s Log message
         */
        virtual void logF(const string s) = 0;
};

} /* LOGGER */
} /* TESTBENCH */
} /* IT */

#endif /* LOGGER_H */
