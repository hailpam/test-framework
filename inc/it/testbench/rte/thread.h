#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#include <support.h>
#include <testbench.h>
#include <rawfsmanager.h>
#include <rawlogger.h>

/**
 * @file thread.h
 * Thread definition. This file defines the Thread class that is basically
 * a wrapper around the Posix pthread library.
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
namespace rte
{


/*!
 * Thread class provides wrapping capabilities for POSIX pthread library. It defines
 * a self contained entity aiming at providing flexibility and decoupling in implementing
 * multithreading applications.
 *
 */
class Thread {

    public:
        Thread();
        virtual ~Thread();

        /**
         * Set Thread unique identifier.
         *
         * @param[in] Reference to the string containing the Thread Id
         */
        void setThreadId(const string& tId);            /*!< set this Thread Id */
        /**
         * Get Thread unique identifier.
         *
         * @return Reference to the string containing the Thread Id
         */
        const string* getThreadId() const;              /*!< return this Thread Id */

        /**
         * Start the Thread and execute the specific business logic defined in the
         * hook method containing the 'custom behaviour'.
         *
         */
        ReturnCode start();                              /*!< run this Thread */
        /**
         * Join to the execution of a previou
         sly started Thread.
         *
         */
        ReturnCode join();                               /*!< pause this Thread */
        /**
         * Detach the execution of a previously paused Thread.
         *
         */
        ReturnCode detach();                             /*!< resume this Thread */
        /**
         * Custom processing functionality. It allows the programmer to extend this wrapper class with
         * its own processing logic.
         *
         */
        virtual void* run() = 0;                         /*!< it defines a custom behaviour to be executed */

        /**
         * Let the caller to know whether ot not this Thread is alive.
         *
         * @return True, iff the Thread is alive.
         */
        bool isThreadAlive();                            /*!< it indicates whether the Thread is still alive */
        /**
         * Let the caller to know whether ot not this Thread is running.
         *
         * @return True, iff the Thread is running.
         */
        bool isThreadRunning();                          /*!< it indicates whether the Thread is still running */
        /**
         * Let the caller to know whether ot not this Thread is busy.
         *
         * @return True, iff the Thread is busy working.
         */
        bool isThreadBusy();                            /*!< it indicates whether the Thread is busy working */

    protected:

        /**
         * Thread Hook. This functionality represents an hook called by the Thread to execute a
         * specific behaviour .
         *
         * @param[in] Pointer to void accepting any kind of parameter type
         *
         */
        static void *threadHook(void* param);            /*!< pointer to member function needed to create a pthread */

        pthread_t thisThread;               /**< it defines itself */
        pthread_attr_t tAttribute;          /**< it defines the attributes of this Thread  */

        string threadId;                    /**< unique identifier for this processing thread */
        bool isBusy;                        /**< it indicates whether or not the thread is busy in elaborations */
        bool isAlive;                       /**< it indicates whether or not the thread is alive*/
        bool isRunning;                     /**< it indicates whether or not the thread is running */

        int threadInit;                     /**< thread indicator: it indicates whether or not the Thread has been correctly initialized */
        int threadJoined;                   /**< initialization indicator: it indicates whether or not the caller requests a join (it is waiting for Thread termination) */
        int threadDetached;                 /**< initialization indicator: it indicates whether or not the caller requests a detach (it is not waiting for Thread termination)*/

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* THREAD_H */


