#ifndef TESTITEM_H
#define TESTITEM_H

#include <support.h>

// $Id$
/**
 * @file testitem.h
 * This module defines the entity Test Item which is very important entity since
 * Test Plans are built by Test Cases and in turn Test Cases by elementary
 * Test Items.
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
class TestCaseContext {
    public:
        TestCaseContext() {}
        virtual ~TestCaseContext() {}
        /**
          * Set the Test Case Context Description
          *
          * @param[in] Pointer to a string containing the description
         */
        virtual void setDescription(const string& description) = 0; //!< set the test case description
        /**
          * Retrieve the Test Case Description
          *
          * @return Pointer to a string containing the description
         */
        virtual const string& getDescription() const = 0;                 //!< get the test case description

    protected:
        string description;                                        /*!< context descriptionc */
};

/*!
* Abstract Data Type defining a generic Test Item that must be spicialized
* according to the needs
*/
class TestItem {
    public:
        TestItem() {}
        virtual ~TestItem() {}
        /**
          * Set up the Test Item in terms of
          *
         */
        virtual TestCaseContext* setupItem() = 0;                           //!< it sets up the item
        /**
          * Run the Test Item
          *
          * @return Pointer to the Report containing the run outcome
         */
        virtual ReturnCode* runItem(TestCaseContext* ctxObject) = 0;      //!< it runs the item
        /**
          * Tear Down the Test Item
          *
          * @param[in] Pointer to a specific Observer entity.
         */
        virtual void tearDownItem(TestCaseContext* ctxObject) = 0;          //!< it tears down the item
};

/*!
* Specific version of Test Item that specifically looks after the creation
* of data structures to be passed using the contextual object.
*/
class SetupTestItem : public TestItem {
    public:
        virtual TestCaseContext* setupItem() = 0;
        ReturnCode* runItem(TestCaseContext* ctxObject);
        void tearDownItem(TestCaseContext* ctxObject);
};

/*!
* Specific version of Test Item that specifically looks after the runtime
* aspect of a Test Case.
*
* It uses the context object to retrieve the specific instances of data
* structures to work on.
*/
class RunnableTestItem : public TestItem {
    public:
        TestCaseContext* setupItem();
        virtual ReturnCode* runItem(TestCaseContext* ctxObject) = 0;
        void tearDownItem(TestCaseContext* ctxObject);
};

/*!
* Specific version of Test Item that looks after the deallocation aspects
* of the data structures allocated and wrapped in the context object.
*/
class TearDownTestItem : public TestItem {
    public:
        TestCaseContext* setupItem();
        ReturnCode* runItem(TestCaseContext* ctxObject);
        virtual void tearDownItem(TestCaseContext* ctxObject) = 0;
};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* TESTITEM_H */
