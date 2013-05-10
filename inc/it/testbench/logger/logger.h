#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// $Id$
/*!
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

/*!
 * Abstract pure Logger interface.
 */
class Logger {
    public:
        /**
         * Trace level logging
         *
         * @param[in] s Log message
         */
        virtual void logT(const string str) = 0;  //!< Trace level logging
        /**
         * Debug level logging
         *
         * @param[in] s Log message
         */
        virtual void logD(const string str) = 0;  //!< Debug level logging
        /**
         * Information level logging
         *
         * @param[in] s Log message
         */
        virtual void logI(const string str) = 0;  //!< Information level logging
        /**
         * Warning level logging
         *
         * @param[in] s Log message
         */
        virtual void logW(const string str) = 0;  //!< Warning level logging
        /**
         * Error level logging
         *
         * @param[in] s Log message
         */
        virtual void logE(const string str) = 0;  //!< Error level logging
        /**
         * Fatal level logging
         *
         * @param[in] s Log message
         */
        virtual void logF(const string str) = 0;  //!< Fatal level logging
};

} /* LOGGER */
} /* TESTBENCH */
} /* IT */

#endif /* LOGGER_H */
