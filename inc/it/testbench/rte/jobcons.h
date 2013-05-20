#ifndef JOBCONS_H
#define JOBCONS_H

#include <list>

#include <thread.h>
#include <syncqueue.h>
#include <support.h>
#include <job.h>


/**
 * @file jobcons.h
 * Thread Consumer definition. This file defines the Thread JobConsumer class
 * that consumes Job objects (wrapper of TestCase) to be consumed.
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
 * Specialized Thread class. It consumes Job objects containing TestCase objects.
 * At the end of the processing, the resulting Report is enqueued and it will be
 * consumed by a report consumer Thread.
 *
 */
class JobConsumer : public Thread {

    public:
        JobConsumer();
        ~JobConsumer();

        /**
         * Custom processing functionality. JobConsumer consumes Job objects realized by TestCase ones
         * and put on the ReportQueue the results of such processing.
         *
         */
        void* run();                                                                       /*!< it defines a custom behaviour to be executed */
        /**
         * Kill the Thread setting up the internal state to not running.
         *
         */
        void killIt();                                                                     /*!< it sets to not running the internal state */
        /**
         * Set the synchronized shared queue on which the jobs must be pushed.
         *
         * @param[in] Pointer to the shared job queue
         * @return Pointer to a ReportCode containing the initialization result
         *
         */
        const ReturnCode* setJobSharedQueue(SynchronizedQueue<Job*>* sharedQueue);         /*!< set the synchronized shared queue */
        /**
         * Set the synchronized shared queue on which the reports must be pushed.
         *
         * @param[in] Pointer to the shared report queue
         * @return Pointer to a ReportCode containing the initialization result
         *
         */
        const ReturnCode* setReportSharedQueue(SynchronizedQueue<Report*>* sharedQueue);  /*!< set the synchronized shared queue */

    private:
        #warning TODO : to be integrated JobWorker State Machine
        SynchronizedQueue<Job*>* jobQueue;            /**< shared queue with job consumers */
        SynchronizedQueue<Report*>* reportQueue;      /**< shared queue with job consumers */

        pthread_mutex_t stateMutex;                   /**< it allows the caller to pause/resume this Thread until new test cases are available */

        bool isPaused;                                /**< it defines whether or not this Thread is paused */

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* JOBCONS_H */


