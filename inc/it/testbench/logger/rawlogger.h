#ifndef RAWLOGGER_H
#define RAWLOGGER_H

#include <logger.h>

#include <fstream>

// $Id$
/*!
 * @file RawLogger.h
 * Raw Logger realized with basic File stream.
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

/*!
 * Implementation of Logger based on simple File stream
 * using the Singleton pattern.
 */
class RawLogger : public Logger {
    private:
        static RawLogger *instance; /*!< static pointer to ensure a single instance */
        static fstream fs;          /*!< File stream used for log file */
        /**
         * Logging service initialization is done at configuration time when
         * a log file path and name is passed.
         */
        RawLogger();
        /**
         * Tear down the Logging service at system shutdown.
         */
        ~RawLogger();
    public:
        /**
         * Return unique instance
         */
        static RawLogger* getInstance();   //!< gets existing instance
        /**
         * Return unique instance and open Log file
         *
         * @param[in] logFile Log file pathname
         */
        static RawLogger* getInstance(const string logFile); //!< gets instance, lazy initialization
        /**
         * Trace level logging
         *
         * @param[in] s Log message
         */
        void logT(const string str);  //!< Trace level logging
        /**
         * Debug level logging
         *
         * @param[in] s Log message
         */
        void logD(const string str);  //!< Debug level logging
        /**
         * Information level logging
         *
         * @param[in] s Log message
         */
        void logI(const string str);  //!< Information level logging
        /**
         * Warning level logging
         *
         * @param[in] s Log message
         */
        void logW(const string str);  //!< Warning level logging
        /**
         * Error level logging
         *
         * @param[in] s Log message
         */
        void logE(const string str);  //!< Error level logging
        /**
         * Fatal level logging
         *
         * @param[in] s Log message
         */
        void logF(const string str);  //!< Fatal level logging
};

} /* LOGGER */
} /* TESTBENCH */
} /* IT */

#endif /* RAWLOGGER_H */
