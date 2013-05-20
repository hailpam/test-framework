#ifndef RTE_H
#define RTE_H

#include <list>

#include <support.h>
#include <observer.h>
#include <jobprod.h>
#include <jobcons.h>
#include <reportcons.h>

#define NR_MAX_OF_THREADS 256

/**
 * @file rte.h
 * Runtime Engine class definition. This file defines the RuntimeEngine class
 * that is the main access point to the core engine capabilities.
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
 * RuntimeEngine class aims at defining the APIs to provide access to the core engine capabilities.
 *
 * It acts as a façade wrapping in simple but effective APIs the asynchronous
 * processing capabilities offered by the core engine behind it.
 *
 * It implements the half sync-async pattern to provide synchronous APIs to the clients,
 * and hiding the asynchronous processing logic offered by the engine.
 *
 * It acts as Subject for entities interested in notifications meanwhile a test plan is
 * under execution. Moreover, itself acts as Observer of report consumer thread to collect
 * the notifications of the running test plan.
 *
 * It implements the Thread Pool pattern, detaching and managing a pool of worker threads.
 *
 */
class RuntimeEngine : public Subject, public Observer {

    public:
        RuntimeEngine();
        ~RuntimeEngine();

        /**
         * Init the core engine. Prior this call, it is not possible to run any Test Plan.
         *
         * @return Pointer to a return code object containing the call outcome
         */
        ReturnCode* initEngine(const unsigned int nrOfWorkers);                                              /*!< initialize the engine */
        /**
         * Destroy the core engine. All threads shall be destroyed, so afterwards no more
         * Test Plan may be run.
         *
         * @return Pointer to a return code object containing the call outcome
         */
        ReturnCode* destroyEngine();                                                                         /*!< destroy the engine */
        /**
         * Let interested entities to subscribe for report notification.
         *
         * @return Pointer to a return code object containing the call outcome
         */
//        ReturnCode* subscribeObserver(const Observer* obs);                                                  /*!< register observers interested in notification messages */
        /**
         * Given the input Test Plan, a call to this method allow to launch such Test Plan
         * in the core engine and to collect the outcomes as many report notifications.
         *
         * @param[in] Pointer to a Testbench configuration file storing the needed information
         * @param[in] Reference to Test Plan Id (unique identifier for a Test Plan)
         * @return Pointer to a return code object containing the call outcome
         */
        ReturnCode* launchTestPlan(const TestBenchConfiguration* tbCfg, const string& tPlanId) throw (TestFrameworkException);       /*!< a sort of command, allow to executed a new test plan */

        /**
         * Provide the caller with the actual worker pool size.
         *
         * @return Actual pool size, as set up on initialization
         */
        const int& actualPoolSize();                                                                           /*!< return the actual worker pool size */

    protected:
        /**
         * Notification call. Every time a new Report is ready to be delivered, the notification
         * consumer call this method to notify the engine.
         *
         * @param[in] Pointer to a Report object
         */
        void notify(Report* report);                                                                        /*!< report consumer notifies using this callback */

    private:
        SynchronizedQueue<Job*>* jobQueue;          /**< job queue, job producer and consumers use this queue */
        SynchronizedQueue<Report*>* reportQueue;    /**< report queue, report producer (job consumer) and consumer use this queue */

        JobProducer* jobProd;                       /**< job producer thread */
        list<JobConsumer*>* jobCons;                /**< job consumer thread */
        ReportConsumer* repCons;                    /**< report consumer thread */

        int poolSize;                               /**< worker thread pool size */

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* RTE_H */


