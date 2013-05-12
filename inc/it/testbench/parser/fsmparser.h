#ifndef FSMPARSER_H
#define FSMPARSER_H

#include <support.h>
#include <rawfsmanager.h>
#include <rawlogger.h>

/**
 * @file fsmparser.h
 * FSM (Finite State Machine) supporting the ParserManager component.
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
 * ParserState defines the base Class for a proper state that can be traversed by the ParserManager.
 *
 * The member funtions are properly redefined in derived class.
 */
class ParserState {

    public:
        ParserState();
        virtual ~ParserState();

        /**
         * Initialization trigger for the FSM.
         *
         * @throw TestFrameworkException
         *
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Return code data structure
         */
        ParserState* init(ReturnCode* report) throw (TestFrameworkException);                                                             /*!< initialization trigger */
        /**
         * Open a predefined stream from the File System. It wraps the bytestream in a string object which is passed back
         * to the caller.
         *
         * @throw TestFrameworkException
         *
         * @param[in] Configuration data structure, it wraps the needed information to open a FS stream
         * @param[inout] Loaded stream, it is a string represenation of the byte read from FS
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Pointer to the next state
         */
        virtual ParserState* open(const Configuration* cfg, string* cfgStream, ReturnCode* report) throw (TestFrameworkException);         /*!< open a string from File System */
        /**
         * Parse the previously opened resource from FS. A smart placeholde is created for each
         * Test Plan defined in the configuration file.
         *
         * @throw TestFrameworkException
         *
         * @param[in] Loaded stream, it is a string represenation of the byte read from FS
         * @param[inout] Pointer to a TestBench data structure which collects the important attributes for every Test Plan
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Pointer to the next state
         */
        virtual ParserState* parse(const string* loadedCfg, TestBench* res, ReturnCode* report) throw (TestFrameworkException);                             /*!< parse an already opened resource */
        /**
         * Validate the loaded Test Bench configuration.
         *
         * @throw TestFrameworkException
         *
         * @param[in] Pointer to Test Bench data structure, it wraps the needed information to open a FS stream
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Pointer to the next state
         */
        virtual ParserState* validate(const TestBench* loadedCfg, ReturnCode* report) throw (TestFrameworkException);                          /*!< validate an already parsed resource */
        /**
         * Reset the FSM. Afeter this call, it will be possible to parse a new configuration.
         *
         * @throw TestFrameworkException
         *
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Pointer to the next state
         */
        virtual ParserState* reset(ReturnCode* report) throw (TestFrameworkException);                                                      /*!< reset the FSM to be ready to accept new requests */
        /**
         * Raised in case of processing error on caller-side: in any case the FSM but be forced to reset for
         * an exceptional condition, this method should be triggered.
         *
         * @throw TestFrameworkException
         *
         * @param[inout] Return code, it allows to report the outcome of the processing to the caller
         *
         * @return Pointer to the next state
         */
        virtual ParserState* error(ReturnCode* report) throw (TestFrameworkException);                                                     /*!< treat an error condition: it is raised any time in the middle of the processing something wrong happens */
        /**
         * Let the caller to discriminate whether or not the FSM is initialized.
         *
         * @return Boolean value, it indicates whether or not the FSM is initialized
         */
        bool isFSMInitialized();                                                                                                           /*!< return a predicate: whether or not the FSM is initialized */

    protected:
        string stateId;             /**< string mainting the state Id (for tracing purpose) */
        bool unInitialized;         /**< defines whether or not the FSM is initialized */

};

class InheritedState : public ParserState
{
    public:
        InheritedState();
        ~InheritedState();

        ParserState* open(const Configuration* cfg, string* cfgStream, ReturnCode* report) throw (TestFrameworkException);
};

/// SPECIFI STATES
class ParserInitialized : public ParserState
{
    public:
        ParserInitialized();
        ~ParserInitialized();

        ParserState* open(const Configuration* cfg, string* cfgStream, ReturnCode* report) throw (TestFrameworkException);
};

class ParserOpened : public ParserState
{
    public:
        ParserOpened();
        ~ParserOpened();

        ParserState* parse(const string* loadedCfg, TestBench* res, ReturnCode* report) throw (TestFrameworkException);
        ParserState* error(ReturnCode* report) throw (TestFrameworkException);

};

class ParserParsed : public ParserState
{
    public:
        ParserParsed();
        ~ParserParsed();

        ParserState* validate(const TestBench* loadedCfg, ReturnCode* report) throw (TestFrameworkException);
        ParserState* error(ReturnCode* report) throw (TestFrameworkException);
};

class ParserValidated : public ParserState
{
    public:
        ParserValidated();
        ~ParserValidated();

        ParserState* reset(ReturnCode* report) throw (TestFrameworkException);
};

class ParserFailed : public ParserState
{
    public:
        ParserFailed();
        ~ParserFailed();

        ParserState* reset(ReturnCode* report) throw (TestFrameworkException);
};


}   /* PARSER */
}   /* TESTBENCH */
}   /* IT */

#endif	/* FSMPARSER_H */
