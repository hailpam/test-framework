
#ifdef syncQueue_H

#include <syncqueue.h>

//namespace it
//{
//namespace testbench
//{
//namespace rte
//{

template <class T>
SynchronizedQueue<T>::SynchronizedQueue()
{
    pthread_mutex_init(&dataMutex, NULL);
    pthread_cond_init(&stateCond, NULL);
}

template <class T>
SynchronizedQueue<T>::~SynchronizedQueue()
{
    pthread_mutex_destroy(&dataMutex);
    pthread_cond_destroy(&stateCond);
}

template <class T>
void SynchronizedQueue<T>::enqueue(T& item) {}

template <class T>
T SynchronizedQueue<T>::dequeue()
{
    T item = syncQueue.pop();
    return item;
}

template <class T>
T SynchronizedQueue<T>::head()
{
    T item = syncQueue.front();
    return item;
}

template <class T>
bool SynchronizedQueue<T>::isEmpty()
{
    return syncQueue.empty();
}

template <class T>
bool SynchronizedQueue<T>::isFull()
{
    if(sizeLimit == 0)
        return false;
    else if(sizeLimit == syncQueue.size())
        return true;
    else
        return false;
}

template <class T>
void SynchronizedQueue<T>::setSizeLimit(int& limit)
{
    sizeLimit = limit;
}

//}   /* RTE */
//}   /* TESTBENCH */
//}   /* IT */

#endif /* to include this implementation in the header file */
