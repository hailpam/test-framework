#ifndef RAWLOGGER_H
#define RAWLOGGER_H

#include <Logger.h>

#include <fstream>

// $Id$
/**
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

/**
 * Implementation of Logger based on simple File stream.
 */
class RawLogger : public Logger {
    private:
        static fstream fs; /** File stream used for log file */
}

} /* LOGGER */
} /* TESTBENCH */
} /* IT */

#endif /* RAWLOGGER_H */
