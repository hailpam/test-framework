#ifndef JOBPROD_H
#define JOBPROD_H

#include <list>

#include <thread.h>
#include <syncqueue.h>
#include <support.h>
#include <job.h>


/**
 * @file jobprod.h
 * Thread Producer definition. This file defines the Thread JobProducer class
 * that produces Job objects (wrapper of TestCase) to be consumed by a JobConsumer
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace rte
{


/*!
 * Specialized Thread class. It produces Job objects by TestCase ones and
 * enqueues such objects on JobQueue. A JobConsumer will be able to retrieve
 * such Job objects and to execute them.
 *
 */
class JobProducer : public Thread {

    public:
        JobProducer();
        ~JobProducer();

        /**
         * Custom processing functionality. JobProducer produces Job objects by TestCase ones
         * and put on the JobQueue such entities.
         *
         */
        void* run();                                                                  /*!< it defines a custom behaviour to be executed */
        /**
         * Kill the Thread setting up the internal state to not running.
         *
         */
        void killIt();                                                                /*!< it sets to not running the internal state */
        /**
         * Set the synchronized shared queue on which the jobs must be pushed.
         *
         * @param[in] Pointer to the shared job queue
         * @return Pointer to a ReportCode containing the initialization result
         *
         */
        const ReturnCode* setJobSharedQueue(SynchronizedQueue<Job*>* sharedQueue);    /*!< set the synchronized shared queue */
        /**
         * Pause the execution of the previously started Thread.
         *
         */
        const ReturnCode* pause();                                                    /*!< pause this Thread */
        /**
         * Resume the execution of the previously paused Thread.
         *
         */
        const ReturnCode* resume();                                                   /*!< resume this Thread */
        /**
         * Allow the caller to Load from outside the test cases to be transformed in jobs
         *
         */
        const ReturnCode* loadTestCases(list<TestCase*>* tCases);                      /*!< load test cases */

    private:
        #warning TODO : to be integrated JobWorker State Machine
        SynchronizedQueue<Job*>* sharedQueue;   /**< shared queue with job consumers */

        pthread_mutex_t stateMutex;             /**< it allows the caller to pause/resume this Thread until new test cases are available */
        pthread_mutex_t dataMutex;              /**< it allows the caller to pause/resume this Thread until new test cases are available */
        pthread_cond_t stateCond;               /**< condition variable on data: it allows signaling among consumer and producers Threads */

        list<TestCase*>* testCases;             /**< externally loaded list of test cases to be executed */

        bool isPaused;                          /**< it defines whether or not this Thread is paused */

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* JOBPROD_H */


