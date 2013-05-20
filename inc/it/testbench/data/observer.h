#ifndef OBSERVER_H
#define OBSERVER_H

#include <map>

#include <support.h>

// $Id$
/**
 * @file observer.h
 * Observer capability to be provided to some test-framework entities.
 *
 * @brief
 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

///  Single line comment for dOxygen.

using namespace std;

namespace it
{
namespace testbench
{
namespace data
{

/*!
* Observer Abstract Data Type: each entity that needs to be asynchronously
* notified should extend this class and register to a Subject
*/
class Observer {
    public:
        /**
          * This method is called each time a registered async callback is ready to be dispatched
          * by the Subject.
          *
          * @param[in] Pointer to a report generated by a test case execution.
         */
        virtual void notify(Report* report) = 0;              //!< virtual function
        /**
          * Return the unique identifier of this Observer
          *
          * @return Pointer to a string containing the unique identifier.
         */
        const string& getWhoAmI() const;                      /*!< observe identifier */
        /**
          * Set the indentifier choose for this observer
          *
          * @param[in] Reference to a string containing the identifier.
         */
        void setWhoAmI(const string& identifier);       /*!< observe identifier */


    protected:
        string whoAmI;                                             /*!< observe identifier */
};

/*!
* Subject Data Type:
*/
class Subject {
    public:
        Subject();
        ~Subject();

        /**
          * Add a new interested entities
          *
          * @param[in] Pointer to a specific Observer entity.
         */
        ReturnCode addObserver(Observer* obs);                      //!< basic behaviour: add an observer
        /**
          * Remove an interested entity (by its own identifier)
          *
          * @param[in] Reference to a string containing the identifier.
          * @return Boolean value, true iff the Observer exists and can be removed
         */
        ReturnCode removeObserver(const string& identifier);        //!< basic behaviour: remove an observer by Id
        /**
          * Whenever new data ara available (in this specific case, new Reports)
          * this method is called to asynchrnously notify all the subscribed observers
          *
          * @param[in] Pointer to a report generated by a test case execution.
         */
        void notifyObservers(Report* report);                       //!< notify all observers
        /**
          * Return the actual number of registered observers
          *
          * @return Number of registered observers
         */
        const unsigned int& actualNrOfObservers();                  //!< notify all observers

    protected:
        map<string, Observer*> obsEntities;             /*!< cached observers (interested entities) */
        map<string, Observer*>::iterator mapItr;        /*!< iterator to the map of observer */

        unsigned int nrOfObservers;                     /*!< counter of registered observers */
};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* OBSERVER_H */
