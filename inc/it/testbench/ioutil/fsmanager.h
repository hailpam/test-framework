#ifndef FSMANAGER_H
#define FSMANAGER_H

#include <string>

// $Id$
/*!
 * @file fsmanager.h
 * File system functionality for the test-framework system.
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
namespace ioutil
{

/*!
* Test Framework custom Exception: it may be raised at rutime
* in case of exceptional situations
*/
class TestFrameworkException : public exception {
    public:
        TestFrameworkException(string msg) throw();     //!< specific Exception constructor
        ~TestFrameworkException() throw();       //!< specific Exception distructor
        /**
          * Overrides the standard behaviour and returns a char pointer to the error string.
          *
          * @return Pointer to the error string.
         */
        const char* what() const throw();       //!< it overwrites the standard version

    private:
        string errMsg;  /*!< runtime error message */
};

/*!
 * Formatted resource data structure
 *
 * TODO: remove this definition during the integration phase
 */
struct FormattedResource {
    string ext; /**< resource extension */
    string content; /**< resource content */
    string name; /**< resource name */
    string hash; /**< resource hash */
};

/*!
 * Abstract pure FSManager interface.
 */
class FSManager {
    public:
        /**
         * Create new file
         *
         * @param[in] fres Resource to create
         */
        virtual void create(const FormattedResource *fres) throw (TestFrameworkException) = 0;    //!< Create new file
        /**
         * Read file
         *
         * @param[inout] fres Resource to read
         */
        virtual void read(FormattedResource *fres) throw (TestFrameworkException) = 0;   //!< Read file
        /**
         * Update file
         *
         * @param[in] fres Resource to write
         */
        virtual void update(const FormattedResource *fres) throw (TestFrameworkException) = 0; //!< Update file
        /**
         * Delete file
         *
         * @param[in] fres Resource to delete
         */
        virtual void remove(const FormattedResource* fres) throw (TestFrameworkException) = 0; //!< Delete file
};

} /* IOUTIL */
} /* TESTBENCH */
} /* IT */

#endif /* FSMANAGER_H */
