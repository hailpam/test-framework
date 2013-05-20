#include <thread.h>


namespace it
{
namespace testbench
{
namespace rte
{

//static void* runThread(void* arg)
//{
//    return ((Thread*)arg)->run();
//}

void *Thread::threadHook(void* param)
{
    // polymorhic call to the specialized method
    if(param != NULL)
        return (reinterpret_cast<Thread*>(param))->run();
    else {
        DATA_ERR_VAL("NULL pointer in Input as parameter", -1);
        return NULL;
    }
}

Thread::Thread() : threadId("Thread"), isBusy(false), isAlive(true), isRunning(false), threadInit(-1), threadJoined(-1), threadDetached(-1)
{
    thisThread = pthread_self();
}

Thread::~Thread() {
    // to be sure that in every moment the wrapped Thread cannot be lost
    pthread_exit(&threadInit);
    DATA_INFO_VAL("Thread exit status", threadInit);
}

void Thread::setThreadId(const string& tId)
{
    threadId = tId;
}

const string* Thread::getThreadId() const
{
    return &threadId;
}

ReturnCode Thread::start()
{
    ReturnCode retCode;
    threadInit = pthread_create(&thisThread, NULL, threadHook, this);
    if(threadInit != 0) {
        retCode.code = ERROR;
        retCode.desc = "Thread not correctly detached";
        DATA_ERR_VAL("Thread not initialized: unsuccessful POSIX Thread creation", -1);
        //
        return retCode;
    }
    //
    isRunning = true;
    retCode.code = SUCCESS;
    retCode.desc = "Thread has been correctly detached";
    DATA_INFO("Thread successfully initialized");
    isRunning = true;
    isAlive = true;
    //
    return retCode;
}

ReturnCode Thread::join()
{
    ReturnCode retCode;
    if(isRunning && threadJoined == 0) {
        retCode.code = ERROR;
        retCode.desc = "Thread is not running or previously joined";
        DATA_ERR_VAL("Thread is not running or previously joined: unsuccessful POSIX Thread join call", -1);
        return retCode;
    }
    //
    threadJoined = pthread_join(thisThread, NULL);
    if(threadJoined != 0) {
        retCode.code = ERROR;
        retCode.desc = "Thread has not been correctly joined: Thread join failed";
        DATA_ERR_VAL("Thread not joined: unsuccessful POSIX Thread join call", -1);
        return retCode;
    }
    //
    retCode.code = SUCCESS;
    retCode.desc = "Thread has been correctly detached";
    DATA_INFO("Thread successfully joined");
    //
    return retCode;
}

ReturnCode Thread::detach()
{
    ReturnCode retCode;
    if(isRunning && threadDetached != 0) {
        retCode.code = ERROR;
        retCode.desc = "Thread is not running or previously detached";
        DATA_ERR_VAL("Thread is not running or previously detached: unsuccessful POSIX Thread detach call", -1);
        return retCode;
    }
    //
    threadDetached = pthread_detach(thisThread);
    if(threadDetached != 0) {
        retCode.code = ERROR;
        retCode.desc = "Thread has not been correctly detached: Thread detach failed";
        DATA_ERR_VAL("Thread not detached: unsuccessful POSIX Thread detach call", -1);
        return retCode;
    }
    //
    retCode.code = SUCCESS;
    retCode.desc = "Thread has been correctly detached";
    DATA_INFO("Thread successfully detached");
    //
    return retCode;
}

bool Thread::isThreadAlive()
{
    return isAlive;
}

bool Thread::isThreadBusy()
{
    return isBusy;
}

bool Thread::isThreadRunning()
{
    return isRunning;
}


}   /* RTE */
}   /* TESTBENCH */
}   /* IT */
