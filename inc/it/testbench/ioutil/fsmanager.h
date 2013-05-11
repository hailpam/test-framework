#ifndef FSMANAGER_H
#define FSMANAGER_H

#include <string>
#include <support.h>

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
using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace ioutil
{

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
