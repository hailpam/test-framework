#ifndef JOB_H
#define JOB_H

#include <support.h>
#include <testbench.h>

/**
 * @file job.h
 * Job definition. This file defines the Job class that wraps a TestCase item.
 * For a worker Thread, a TestCase item consists in the basic unit of work.
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

using namespace std;
using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace rte
{


/*!
 * Job class defines a work item for a worker thread. It wrapes in
 * the TestCase class.
 *
 */
class Job {

    public:
        Job();
        ~Job();

        /**
         * Once the TestCase has been correctly set, a call to this method allows to
         * executed all test items and collect the resutls;
         *
         * @param[in] Pointer to the generated Report object
         * @return Pointer to a ReturnCode object
         *
         */
        ReturnCode* executeTestCase();
        /**
         * Once the TestCase has been executed, a call to this method allows to
         * generate an aggregate Report containing the execution result.
         *
         * @param[in] Pointer to the generated Report object
         * @return Pointer to a ReturnCode object
         *
         */
        ReturnCode* generateReport(Report* genReport);
        /**
         * Set the TestCase as unit of work.
         *
         * @param[in] Pointer to the TestCae
         * @return Pointer to a ReturnCode object
         *
         */
        ReturnCode* setTestCase(const TestCase* tCase);

    private:
        TestCase* tCase;        /**< pointer to the TestCase that should be executed */

        bool tCaseExecuted;     /**< it indicates whether or not the TestCase has been executed */

};

}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* JOB_H */
