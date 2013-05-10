#ifndef TEST_STUB_FSMANAGER_H
#define TEST_STUB_FSMANAGER_H

#include <fsmanager.h>

// $Id$
/*!
 * @file test_stubfsmanager.h
 * File system manager Stub for unit testing purposes.
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

/**
 * Helper class StubFSManager that replicates
 * the state of the RawFSManager with assertions
 * to check the correctness of the operations
 */
class StubFSManager : public FSManager {
    private:
        pthread_mutex_t fsMux;  // protect private variables
        string fsState; // mimics only the fres->content field
        bool fileCreated; // keeps track of the created/removed state
    public:
        /**
         * Initialize mutex and internal start with no file yet present
         */
        StubFSManager();
        /**
         * Destroy mutex
         */
        virtual ~StubFSManager();
        /**
         * Create new file
         *
         * @param[in] fres Resource to create
         */
        void create(const FormattedResource *fres);
        /**
         * Read file
         *
         * @param[inout] fres Resource to read
         */
        void read(FormattedResource *fres);
        /**
         * Update file
         *
         * @param[in] fres Resource to write
         */
        void update(const FormattedResource *fres);
        /**
         * Delete file
         *
         * @param[in] fres Resource to delete
         */
        void remove(const FormattedResource* fres);
};

} /* IOUTIL */
} /* TESTBENCH */
} /* IT */

#endif /* TEST_STUB_FSMANAGER_H */