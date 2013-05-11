#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <support.h>
#include <list>
#include <vector>
#include <map>
#include <sstream>

#include <testitem.h>


// $Id$
/**
 * @file testbench.h
 * This module defines the Test Bench, Test Plan and Test Case entities.
 * They are strictly related eaexch others and define a contextual runnable
 * object: the Test Cases contained in the Test Plan are treated as many
 * parallel executable jobs by the internal test bench engine.
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
* Abstract Data Type defining a Context Object that is used among the several
* Test Items contextually to a Test Case run.
*
* This class must be subclassed in order to contain the specific data types
* to be passed among the methods.
*/
class TestCase {
    public:
        TestCase();
        ~TestCase();                                                            //!< it deallocates the dynamic instances
        /**
          * Initialize the data structure specific to this Test Case
          *
          * @return Boolean value, true if everythig gone well
         */
        void setupTestCase() throw(TestFrameworkException);                     //!< set up a Test Case
        /**
          * Executes the Test Items specific to this Test Case
          *
          * @return Boolean value, true if everythig gone well
         */
        void runTestCase() throw(TestFrameworkException);                       //!< execute a Test Case
        /**
          * Tear down the data structures initialized for this Test Case
          *
          * @return Boolean value, true if everythig gone well
         */
        void tearDownTestCase() throw(TestFrameworkException);                  //!< tear down a Test Case

        /**
          * Set up the specific SetupTestItem (particularized instance)
          *
          * @param[in] Pointer to a specific setup test item
         */
        void setSetupTestItem(const SetupTestItem* sTestItem);                  //!< set the Setup Test Item
        /**
          * Set up the specific TearDownTestItem (particularized instance)
          *
          * @param[in] Pointer to a specific tear down test item
         */
        void setTearDownTestItem(const TearDownTestItem* tdTestItem);           //!< set the Tear down Test Item
        /**
          * Set the Test Case Context Description
          *
          * @param[in] Pointer to a specific TestCaseContext
         */
        void setTestCaseContextObject(const TestCaseContext* tcCtxObject);      //!< set the Test Case Context Object
        /**
          * Add a specific RunnableTestItem (particularized instance)
          *
          * @param[in] Pointer to a specific runnable test item
         */
        void addRunnableTestItem(const RunnableTestItem* rTestItem);            //!< add a Runnable Test Item to the list
        /**
          * Add a report to a list of reports generated by runnable Test Items
          *
          * @param[in] Pointer to a report object
         */
        void addReport(const Report* report);                                   //!< add a Report to the list
        /**
          * Set the Test Case number
          *
          * @param[in] An integer representing the test case number
         */
        void setTestCaseNumber(const unsigned int& tcNo);                       //!< set the test case number
        /**
          * Get the Test Case number
          *
          * @return An integer representing the test case number
         */
        const int getTestCaseNumber() const;                                     //!< return the test case number
        /**
          * Finalize the reports by the single Items creating a merged and final Report
          *
          * @return Pointer to a newly created Report
         */
        Report* finalizeReport();                                               //!< finalize the report by the reports of the single test items

    private:
        SetupTestItem* sTestItem;               /*!< specific test item looking after the setup */
        list<RunnableTestItem*> rTestItems;     /*!< specific test item looking after the run aspects */
        TearDownTestItem* tdTestItem;           /*!< specific test item looking after the deallocation */
        list<Report*> tcReports;                /*!< list of reports (one for each runnable item */
        TestCaseContext* ctxObject;             /*!< context object: it maintanis the pointers to specific data structures to be used */
        unsigned int tcNumber;                  /*!< test case number: it is an identifier */
};

/*!
* It defines a Data Structure that is basically a collection of Test Cases.
*
* Each Test Case will be executed independently.
*/
// TODO : create an Utility for conversions : avoid string stream in each class
class TestPlan {
    public:
        TestPlan();
        ~TestPlan();
        /**
          * Add a Test Case (addressed by an ordinal number)
          *
          * @param[in] Index where to put the Test Case
          * @param[in] Pointer to a Test Case object
         */
        ReturnCode addTestCase(unsigned int tcIdx, const TestCase* tCase);        //!< add a Test Case
        /**
          * Retrieve a specific Test Case (addressed by an ordinal number)
          *
          * @param[in] Index of the Test Case
          * @return Pointer to a Test Case object
         */
        const TestCase* retrieveTestCase(unsigned int tcIdx) const;          //!< retrieve a Test Case
        /**
          * Remove a specific Test Case (addressed by an ordinal number)
          *
          * @param[in] Index of the Test Case
          * @return Boolean value, true if the Test Case was present and updated
         */
        ReturnCode removeTestCase(unsigned int tcIdx);                             //!< remove a Test Case
        /**
          * Update a specific Test Case (addressed by an ordinal number)
          *
          * @param[in] Index of the Test Case
          * @return Boolean value, true if the Test Case was present and updated
         */
        ReturnCode updateTestCase(unsigned int tcIdx, const TestCase* tCase);      //!< update a Test Case
        /**
          * Update a specific Test Case (addressed by an ordinal number)
          *
          * @return Boolean value, true if the Test Case was present and updated
         */
        const int getNrOfTestCases();                                        //!< get the number of test cases

    private:
        vector<TestCase*> listOfTests;                              /*!< list of Test Cases composing this Test Plan */
        vector<TestCase*>::iterator itrList;                        /*!< iterator to the vector structure */
};


/*!
* Test Bench configuration abstract Data Type.
*
* It maintains alle the needed information to automatically run the Test Plan
* (on Test Case basis) in a specialized instance of Testbench.
*/
class TestBenchConfiguration {
    public:
        TestBenchConfiguration();
        ~TestBenchConfiguration();

        /**
          * Set the Session Id (unique identifier for a Testbench context)
          *
          * @param[in] Pointer to a string containing the session Id
         */
        ReturnCode setSessionId(const string& sId);                                 //!< set the session Id (unique identifier for each test bench instance)
        /**
          * Retrieve the Sesssion Id
          *
          * @return Pointer to a string containing the session Id
         */
        const string* getSessionId() const;                                   //!< get the session Id
        /**
          * Add a Range data structure (identifying the range of Test Cases to be run)
          *
          * @param[in] Pointer to a string containing the test plan Id
          * @param[in] Pointer to a Range data structure
         */
        ReturnCode addRange(const string& tPlanId, const Range& range);             //!< add a Range
        /**
          * Retrieve the Range associated to a specific Test Plan
          *
          * @param[in] Pointer to a string containing the test plan Id
          * @return Pointer to a Range data structure
         */
        const Range* retrieveRange(const string* tPlanId);               //!< retrieve a Range
        /**
          * Set the supported format (specific for data serialization matters)
          *
          * @param[in] Supported format
         */
        void setSupporterFormat(SupportedFormats format);                     //!< set the supported Format
        /**
          * Retrieve the supported format
          *
          * @return The supported format
         */
        SupportedFormats getSupportedFormat();                                //!< get the supported Format
        /**
          * Set the number of threads (to be used at runtime by the testbench)
          *
          * @param[in] The number of threads desired to run the test plan
         */
        void setNrOfThreads(unsigned int threadNo);                           //!< set the number of threads to be used
        /**
          * Get the number of threads (used at runtime by the testbench)
          *
          * @return The number of threads
         */
        int getNrOfThreads();                                                 //!< get the defined number of threads
        /**
          * Add a Test Plan object
          *
          * @param[in] Pointer to a string containing the test plan Id
          * @param[in] Pointer to a Test Plan object
         */
        ReturnCode addTestPlan(const string* tPlanId, TestPlan* tPlan);            //!< add a test plan
        /**
          * Retrieve a specific Test Plan object
          *
          * @param[in] Pointer to a string containing the test plan Id
          * @return Pointer to a Test Plan object
         */
        const TestPlan* retrieveTestPlan(const string* tPlanId);             //!< retrieve a test plan

    private:
        string sessionId;                                                   /*!< specific and unique session Id */
        map<string, Range*> tcToBeExecuted;                                 /*!< for each Test Plan, a range of tests to be executed */
        SupportedFormats format;                                            /*!< supported format */
        unsigned int nrOfThreads;                                                    /*!< number of thread to be used at runtime */
        map<string, TestPlan*> pTestPlan;                                   /*!< the set of Test Plan to be executed in this testbench */
};

/*!
* Abstract Data Type defining a Test Case Builder.
*
* At run time, a concrete builder will provide the ability to build specific test cases
* based on specific Test Items: the programmer has to write only the specific source code
* for the Test Item and a specifc Test Case builder.
*
* Applying the buildre pattern strategy, the engine will be completely decoupled.
*/
class TestCaseBuilder {
    public:
        /**
          * To be overriden specifically. Each concrete Test Case builder provides the ability
          * to fully decouple the building process.
          *
          * @return Boolean value, true iff the building has been performed successfully
         */
        virtual TestCase* buildTestCase() = 0;   //!< build a specific instance of Test Case
};

/*!
* Its main responsibility consists in using the specific test case builders that will create
* as many specific Test Cases.
*
* This entity is very useful to decouple the caller (that wants only many Test Cases instances
* already created) from the entity delegated to concretely build the Test Cases instances.
*/
class TestCaseLoader {
    public:
        TestCaseLoader();
        ~TestCaseLoader();

        /**
          * To be overriden specifically. Each concrete Test Case builder provides the ability
          * to fully decouple the building process.
          *
          * @return Boolean value, true iff the loading has been performed successfully
         */
        bool loadTestCase(unsigned int tcIdx);                              //!< load a specific test case
        /**
          * To be overriden specifically. Each concrete Test Case builder provides the ability
          * to fully decouple the building process.
          *
          * @return Boolean value, true iff the loading has been performed successfully
         */
        bool loadAllTestCases();                                            //!< load all test cases

        /**
          * To be overriden specifically. Each concrete Test Case builder provides the ability
          * to fully decouple the building process.
          *
          * @return Point to the Test Case, 0 iff the Test Case has not been built yet
         */
        const TestCase* getLoadedTestCase(unsigned int tcIdx) const;                    //!< retrieve the specified test case
        /**
          * To be overriden specifically. Each concrete Test Case builder provides the ability
          * to fully decouple the building process.
          *
          * @return List of Test Cases pointers, it is empty iff the test cases have not been yet built
         */
        const vector<TestCase*>* getAllLoadedTestCases() const;                            //!< retrieve all test cases

        /**
          * To register the list of specific builder that should be used to create the Test Cases
          *
          * @param[in]
          * @return A boolean, true iff the registration was successful
         */
        bool registerTestCaseBuilder(unsigned const int tcIdx, const TestCaseBuilder* tcBuilder);

    private:
        vector<TestCase*> tcList;                           /*!< list of test cases */
        vector<TestCaseBuilder*> tcBuilders;                /*!< point to a list of test case builder */
        vector<TestCase*>::iterator itrList;                /*!< iterator to list of test cases */
        vector<TestCaseBuilder*>::iterator itrBuildList;    /*!< iterator to list of builders  */
};


} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* TESTBENCH_H */
