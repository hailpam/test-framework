#ifndef RAWFSMANAGER_H
#define RAWFSMANAGER_H

#include <logger.h>
#include <pthread.h>
#include <fstream>

// $Id$
/*!
 * @file rawfsmanager.h
 * File System Manager realized with basic File stream.
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
 * Implementation of Logger based on simple File stream
 * using the Singleton pattern.
 */
class RawFSManager : public FSManager {
    private:
        static RawFSManager *instance; /*!< static pointer to ensure a single instance */
        static fstream fs;          /*!< File stream used for log file */
        static pthread_mutex_t fsMux;  /*!< mutex for protecting static variables */
        /**
         * Logging service initialization is done at configuration time when
         * a log file path and name is passed.
         */
        RawFSManager();
        /**
         * Tear down the Logging service at system shutdown.
         */
        ~RawFSManager();
    public:
        /**
         * Return unique instance
         */
        static RawFSManager* getInstance();   //!< gets existing instance
        /**
         * Create new file
         *
         * @param[in] fres Resource to create
         */
        void create(const FormattedResource *fres);    //!< Create new file
        /**
         * Read file
         *
         * @param[inout] fres Resource to read
         */
        void read(FormattedResource *fres);   //!< Read file
        /**
         * Update file
         *
         * @param[in] fres Resource to write
         */
        void update(const FormattedResource *fres); //!< Update file
        /**
         * Delete file
         *
         * @param[in] fres Resource to delete
         */
        void del(const FormattedResource* fres); //!< Delete file
};

} /* IOUTIL */
} /* TESTBENCH */
} /* IT */

#endif /* RAWFSMANAGER_H */
