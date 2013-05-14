#ifndef FORMATTER_MANAGER_H
#define FORMATTER_MANAGER_H

#include <string>
#include <map>
#include <support.h>
#include <formatter_functor.h>

// $Id$
/**
 * @file formatter_manager.h
 * This module defines the Formatter Manager, which has the function
 * to format a Report object for output both on console and on file.
 * It offers a Facade to call at runtime the needed Functor, that shall
 * implement formatting in the requested format.
 *
 * @brief

 *
 * @author Raffaele Aquilone <aquiloneraf@gmail.com>
 * @version 0.1
 */
// $Log$

///  Single line comment for dOxygen.

using namespace std;
using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace formatter
{

/*!
 * Facade of the Formatter package to offer formatting functionalities
 * to TCWorker threads (or possibly any other entity in the system)
 * to make Report objects ready for output
 */
class FormatterManager {
    public:
        FormatterManager();
        ~FormatterManager();
        /**
         * Reads configuration from the report and formats it
         * for console output
         *
         * @param[inout] Report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode formatForConsole(Report* report) throw (TestFrameworkException);
        /**
         * Reads configuration from the report and formats it
         * for file output
         *
         * @param[inout] Report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode formatForFile(Report* report) throw (TestFrameworkException);
    private:
        map<string, FormatterFunctor*> fmtFunctor;	/*!< hashmap of available format functors for file output */
        ConsoleFunctor* cslFunctor;                 /*!< formatter for console output */
};

} /* IT */
} /* TESTBENCH */
} /* FORMATTER */

#endif /* FORMATTER_MANAGER_H */
