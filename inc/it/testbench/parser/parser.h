#ifndef PARSER_H
#define PARSER_H

#include <support.h>
#include <testbench.h>
#include <rawfsmanager.h>
#include <rawlogger.h>
#include <fsmparser.h>

/**
 * @file parser.h
 * Parser definition. This file defines the parser manager that looks after
 * all needed parsing operations and creation of testbench context objects.
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

using namespace std;

using namespace it::testbench::data;
using namespace it::testbench::logger;
using namespace it::testbench::ioutil;

namespace it
{
namespace testbench
{
namespace parser
{


/*!
 * ParserManager component provides the capabilities to safely load, parse and validate a configuration file.
 *
 * Internally, an instance of ParserManager acts an FSM (Finite State Machine) for which the processing flow
 * is well defined: O = f(I, S), its implementation is done using a Moore machine model.
 */
class ParserManager {
    public:
        ParserManager();
        ~ParserManager();

        /**
         * Load the configuration files uniquely specifying the Test Plan to be run.
         *
         * @throw TestFrameworkException
         * @param[in] Configuration data structure, it wraps the needed information to open a FS stream
         */
        void loadConfig(const Configuration& fileCfg) throw (TestFrameworkException);   /*!< load the desired configuration file */
        /**
         * Parse the previously loaded configuration file and in case of error throws an exception.
         *
         * @throw TestFrameworkException
         */
        void parseConfig() throw (TestFrameworkException);                              /*!< parse the loaded configuration */
        /**
         * Validate the previously loaded configuration file. The results are logged and returned in the ReportCode
         * data structured.
         *
         * @return Report code data, it wraps the outcome of the initialization
         */
        ReturnCode validateConfig();                                                    /*!< validate configuration */
        /**
         * To be overriden specifically. Each concrete Test Case builder provides the ability
         * to fully decouple the building process.
         *
         * @return Report code data, it wraps the outcome of the initialization
         */
        ReturnCode init(const TestCaseLoader* loader);                                  /*!< initialize the Parser Manager */

    private: /* here the state */
        string* loadedStream;           /**< loaded stream from File System */
        TestCaseLoader* tcLoader;       /**< loader/builder of test cases */
        Configuration* loadedCfg;       /**< loaded configuration */
        ParserState* currentState;      /**< it maintains the current state */
        TestBench* tbParsed;            /**< parsed setting from the configuration file */
};


}   /* PARSER */
}   /* TESTBENCH */
}   /* IT */

#endif	/* PARSER_H */
