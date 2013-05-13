#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <exception>
#include <list>
#include <debug.h>


#define NR_OF_THREADS 50

// $Id$
/**
 * @file support.h
 * Support types for the test-framework system.
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

///  Single line comment for dOxygen.

using namespace std;

namespace it
{
namespace testbench
{
namespace data
{

/*!
* Code enumeration
*/
enum Code {
    ERROR,          /**< error indicator*/
    SUCCESS         /**< success indicator*/
};

/*!
* Supported formats enumeration (for serialization)
*/
enum SupportedFormats {
    CSV,            /**< CSV data format */
    JSON,           /**< JSON data format */
    XML,            /**< XML data format */
    CUSTOM          /**< CUSTOM data format */
};

/*!
* Return code data structure
*/
struct ReturnCode {
    Code code;      /**< enumeration containing the codes*/
    string desc;    /**< specific description*/
};

/*!
* Formatted resource data structure
*/
struct FormattedResource {
    string ext;     /**< resource extension */
    string content; /**< resource content */
    string name;    /**< resource name */
    string hash;    /**< resource hash */
};

/*!
* Range data structure: useful to defines ranges to be taken into
* consideration at runtime
*/
struct Range {
    int from;           /**< start index */
    int to;             /**< end index */
};

/*!
* Test Framework custom Exception: it may be raised at rutime
* in case of exceptional situations
*/
class TestFrameworkException : public exception {
    public:
        TestFrameworkException(string msg)  throw();                                    //!< specific Exception constructor
        ~TestFrameworkException() throw();                                              //!< specific Exception distructor
        /**
          * Overrides the standard behaviour and returns a char pointer to the error string.
          *
          * @return Pointer to the error string.
         */
        const char* what() const throw();                       //!< it overwrites the standard version

    private:
        string errMsg;  /*!< runtime error message */
};

/*!
* Report data type containing the elaboration outcome
*/
class Report {
    private:
        string* sessionId;              /*!< testbench unique session identifier */
        string* testPlanId;             /*!< test plan unique identifier */
        unsigned int testId;            /*!< test case unique identifier */
        list<ReturnCode*>* retCodes;    /*!< elaboration outcome */
        FormattedResource* resource;    /*!< resource formatted according to initial settings */

    public:
        Report();
        ~Report();
        /**
          * Return the processing outcome.
          *
          * @return A boolean value, true if the processing was successful.
         */
        list<ReturnCode*>* getOutcome();                         //!< return the outcome
        /**
          * Set the processing outcome.
          *
         */
        void setOutcome(list<ReturnCode*>* retCodes);      //!< set the outcome

        /**
          * Return the session Id detached by the testbench manager for the specific Test Plan.
          *
          * @return Pointer to a string containing the unique identifier.
         */
        const string* getSessionId();                           //!< return the session Id
        /**
          * Set the session Id according to the testbench configuration.
          *
          * @param[in] A pointer to a string containing the session identifier.
         */
        void setSessionId(const string* sId);             //!< set the session Id

        /**
          * Return the testplan Id which is the unique identifier for the running Test Plan.
          *
          * @return Pointer to a string containing the unique identifier.
         */
        const string* getTestPlanId();                          //!< return the test plan Id
        /**
          * Set the test plan Id according to the testbench configuration.
          *
          * @param[in] A pointer to a string containing the test plan identifier.
         */
        void setTestPlanId(const string* tpId);           //!< set the test plan Id

        /**
          * Return the test Id which is a unique identifier for the Test Case in the running context.
          *
          * @return Pointer to the string containing the identifier.
         */
        const unsigned int getTestId();                    //!< return the test Id
        /**
          * Set the test case Id according to the testbench configuration
          *
          * @param[in] A pointer to a string containing the test case number
         */
        void setTestId(const unsigned int tId);                 //!< set the test Id

        /**
          * Set the formatted resource provided by the Formatter (it takes care to mediate
          * among the formats, according to the configuration).
          *
          * @param[in] A pointer to the received formatted resource.
         */
        void setFormattedResorce(FormattedResource* res);   //!< set the formatted resource
        /**
          * Return the formatted resource.
          *
          * @return Pointer to the formatted resource.
         */
        const FormattedResource* getFormattedResource();        //!< return the formatted resource
};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif  /* SUPPORT_H */
