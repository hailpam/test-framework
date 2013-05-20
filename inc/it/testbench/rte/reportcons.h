#ifndef REPORTCONS_H
#define REPORTCONS_H

#include <list>

#include <thread.h>
#include <syncqueue.h>
#include <support.h>
#include <observer.h>


/**
 * @file reportcons.h
 * Thread Consumer definition. This file defines the Thread ReportConsumer class
 * that consumes Report objects generated and enqueued by Report Consumers.
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
 * Specialized Thread class. It consumes Reports provided by Job Consumers.
 * It formats the reports and then notifies all its observers about the new
 * available formatted reports.
 *
 */
class ReportConsumer : public Thread, public Subject {

    public:
        ReportConsumer();
        ~ReportConsumer();

        /**
         * Custom processing functionality. ReportConsumer consumes Report objects
         * put on the Queue by JobConsumer.
         *
         */
        void* run();                                                                       /*!< it defines a custom behaviour to be executed */
        /**
         * Kill the Thread setting up the internal state to not running.
         *
         */
        void killIt();                                                                     /*!< it sets to not running the internal state */
        /**
         * Set the synchronized shared queue on which the reports must be pushed.
         *
         * @param[in] Pointer to the shared report queue
         * @return Pointer to a ReportCode containing the initialization result
         *
         */
        const ReturnCode* setReportSharedQueue(SynchronizedQueue<Report*>* sharedQueue);  /*!< set the synchronized shared queue */

    private:
        #warning TODO : to be integrated with Report Formatter
        SynchronizedQueue<Report*>* reportQueue;      /**< shared queue with job consumers */

        bool isPaused;                                /**< it defines whether or not this Thread is paused */

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* REPORTCONS_H */


