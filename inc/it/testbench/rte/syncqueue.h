#ifndef SYNCQUEUE_H
#define SYNCQUEUE_H

#include <pthread.h>

#include <queue>

/**
 * @file syncqueue.h
 * Synchronized Queue definition. This file defines the SynchronizedQueue template class
 * that allows to multiple entities (producers and consumers) to work concurrently
 * on the data stored by this data structure.
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

using namespace std;

namespace it
{
namespace testbench
{
namespace rte
{


/*!
 * Synchronized Queue is a template class allowing a synchronized access to its
 * internal state.
 *
 * FIFO (First-In, First-Out) policy provided by the interface.
 *
 * It wraps POSIX pthread synchronization mechanisms.
 *
 */
template <class T>
class SynchronizedQueue {

    public:
        SynchronizedQueue() {
            pthread_mutex_init(&dataMutex, NULL);
            pthread_mutex_init(&stateMutex, NULL);
            pthread_cond_init(&stateCond, NULL);

            sizeLimit = 0;
            label = "Synchronize Queue";
        }
        ~SynchronizedQueue() {
            pthread_mutex_destroy(&dataMutex);
            pthread_mutex_init(&stateMutex, NULL);
            pthread_cond_destroy(&stateCond);
        }

        /**
         * Push back in the container the item passed as Input
         *
         * @param[in] Reference to the element to be pushed back in the container
         *
         */
        void enqueue(T item){
//            DATA_INFO_VAL("@Synchronized Queue #", label);
            pthread_mutex_lock(&dataMutex);
//            DATA_INFO_VAL("Enqueuing an element, current size #", syncQueue.size());
            syncQueue.push(item);
            counter++;
            DATA_INFO_VAL("Element enqueued (Signal raised), current size #", syncQueue.size());

            pthread_cond_signal(&stateCond);
            pthread_mutex_unlock(&dataMutex);
        }              /*!< push back the data element in the container */
        /**
         * Remove from the container the topmost element (decrease the size)
         *
         * @return Reference to the topmost element in the container
         *
         */
        T dequeue() {
            pthread_mutex_lock(&dataMutex);
//            DATA_INFO_VAL("@Synchronized Queue #", label);
//            DATA_INFO_VAL("Dequeuing an element, current size #", syncQueue.size());
            DATA_INFO_VAL("Is empty? #", syncQueue.empty());
            while(counter == 0)
                pthread_cond_wait(&stateCond, &dataMutex);
            T item;
            if(counter > 0) {               //to protect: likely bug in pop -->> to be verified
                item = syncQueue.front();
                syncQueue.pop();
                counter--;
            }
            pthread_mutex_unlock(&dataMutex);
            DATA_INFO_VAL("Element dequeued (Mutex released), current size #", syncQueue.size());
            return item;
        }                       /*!< retrieve the front element in the container */
        /**
         * Provide a reference of the topmost element stored in the container (no size decreasing)
         *
         * @return Reference to the topmost element in the container
         *
         */
        T head() {
            pthread_mutex_lock(&dataMutex);
            T item = syncQueue.front();
            pthread_mutex_unlock(&dataMutex);
            return item;
        }                          /*!< analyse the front element in the container */

        /**
         * Check whether the container is empty (no item is stored)
         *
         * @param[in] Boolean value, true iff the container is empty
         *
         */
        bool isEmpty() {
            pthread_mutex_lock(&dataMutex);
            bool outcome = syncQueue.empty();
            pthread_mutex_unlock(&dataMutex);
            return outcome;
        }                     /*!< check whether the container is empty */
        /**
         * Check whether the container is full (not able to accept items anymore)
         *
         * @param[in] Boolean value, true iff the container is full
         *
         */
        bool isFull() {
            pthread_mutex_lock(&dataMutex);
            bool outcome;
            if(sizeLimit == 0)
                outcome = false;
            else if(sizeLimit == syncQueue.size())
                outcome = true;
            else
                outcome = false;
            pthread_mutex_unlock(&dataMutex);
            return outcome;
        }                      /*!< check whether the container is full */

        /**
         * Set the maximum number of pushable elements
         *
         * @param[in] Maximum number of pushable elements
         *
         */
        void setSizeLimit(const int& limit) {
            pthread_mutex_lock(&dataMutex);
            sizeLimit = limit;
            pthread_mutex_unlock(&dataMutex);
        }      /*!< push back the data element in the container */

        /**
         * Set the lable for this data structure
         *
         * @param[in] Label to be assigned
         *
         */
        void setLabel(const string& strLabel) {
            pthread_mutex_lock(&dataMutex);
            label = strLabel;
            pthread_mutex_unlock(&dataMutex);
        }      /*!< set a label for this data structure */

        /**
         * Set the lable for this data structure
         *
         * @param[in] Label to be assigned
         *
         */
        const string getLabel() {
            pthread_mutex_lock(&dataMutex);
            string tmp = label;
            pthread_mutex_unlock(&dataMutex);
            return tmp;
        }      /*!< get the label for this data structure */

    protected:
        pthread_mutex_t dataMutex;      /**< mutex on data: it guarantee mutual exclusive access on data */
        pthread_mutex_t stateMutex;     /**< mutex on state: it guarantee mutual exclusive access on predicate */
        pthread_cond_t stateCond;       /**< condition variable on data: it allows signaling among consumer and producers Threads */

        queue<T> syncQueue;             /**< queue container of generica data T */

        unsigned int sizeLimit;         /**< it defines a size limit if needed */
        string label;                   /**< it defines a label for this data structure */
        unsigned int counter;

};


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */

#endif	/* SYNCQUEUE_H */


