#include <rawfsmanager.h>
#include "test_stubfsmanager.h"
#include <debug.h>
#include <string>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <cstdio>

using namespace std;
using namespace it::testbench::ioutil;

/**
 * Helper functions
 */

/**
 * Check if file exists
 */
bool fileExists(const string filename);

void hexPrint(const char* str){
    int i = 0;
    while (str[i] != '\0')
        printf("0x%x ", str[i++]);
    printf("\n");
}

/**
 * Clean resources
 */
void clearRes(FormattedResource *fres){
    fres->ext.clear();
    fres->content.clear();
    fres->name.clear();
    fres->hash.clear();
}

/**
 * Shared pointer used by worker threads to refer to the
 * Stub FSManager object
 */
static StubFSManager *stubMng;
static pthread_mutex_t stubMux = PTHREAD_MUTEX_INITIALIZER;
const int THD_NUM = 100;    /* Number of threads writing to log */
const int MSG_NUM = 1000;   /* Number of messages sent by each thread */
static string concFile = "test_concurrency_rawfsmanager";

void* fs_bombing_function(void *arg){
    /**
     * Get the thread index from the caller and
     * initialize all local variables
     */
    int thd_idx = *((int*)arg);
    delete (int*)arg;
    stringstream strStream;
    strStream.str(string());
    RawFSManager *fsMng = RawFSManager::getInstance();
    FormattedResource *fresActual = new FormattedResource();
    FormattedResource *fresStub = new FormattedResource();
    /**
     * Storm the FS, reply on the Stub and check the 2 results
     */
    for (int i = 0; i < MSG_NUM; i++) {
        clearRes(fresActual);
        clearRes(fresStub);
        fresActual->name = concFile;
        fresActual->ext = "txt";
        if (pthread_mutex_lock(&stubMux) < 0)
            continue;
        switch ( (i + thd_idx) % 4)  {
                case 0 : { // create
                    fsMng->create(fresActual);
                    stubMng->create(fresStub);
                    PRINT(">> Create");
                    break;
                }
                case 1 : { // read
                    fsMng->read(fresActual);
                    stubMng->read(fresStub);
                    PRINT(">> Read");
                    break;
                }
                case 2 : { // update
                    strStream.str(string());
                    strStream <<"[thread " <<thd_idx <<": iteration " <<i <<"]";
                    fresActual->content = strStream.str();
                    fresStub->content = strStream.str();
                    fsMng->update(fresActual);
                    stubMng->update(fresStub);
                    PRINT(">> Update " <<fresActual->content);
                    break;
                }
                case 3 : { // remove
                    fsMng->create(fresActual);
                    stubMng->create(fresStub);
                    PRINT(">> Remove");
                    break;
                }
        }
        PRINT("Actual: " <<fresActual->content <<"   Stub: " <<fresStub->content);
        ASSERT_STRING_EQUAL(fresActual->content, fresStub->content);
        pthread_mutex_unlock(&stubMux);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    /**
     * Setup: prepare string
     */
    string testExistingString = "This is a known string\n";
    string testNewString = "Greetings from RawFSManager";
    string testDirtyString = "Here there is only rubbish";
    string testEmptyString;
    testEmptyString.clear();
    string testRead, testWrite;
    string wrongFile = "subdir/test_rawfoo";
    string absentFile = "test_rawabsent";
    string existingFile = "test_rawfsmanager";
    string newFile = "test_second_rawfsmanager";
    string fileTxt = "txt";
    FormattedResource *fres = new FormattedResource;
    RawFSManager *fsman;

    /**
     * getInstance() from RawFSManager
     *
     * Expected value: 0
     */
    fsman = RawFSManager::getInstance();
    PRINT("getInstance() from RawFSManager");
    PRINT("    returned pointer: " <<fsman);
    ASSERT_NOT_EQUAL(fsman, 0);
    if (!fsman)
        return -1;

    /**
     * Create file with wrong filename
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = wrongFile;
    fsman->create(fres);
    PRINT("create file with wrong filename");
    PRINT("    " <<wrongFile <<".txt");
    ASSERT_EQUAL(fileExists(wrongFile + ".txt"), false);

    /**
     * Create file that doesn't exist
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fsman->create(fres);
    PRINT("create file that doesn't exist");
    PRINT("    " <<newFile <<".txt");
    ASSERT_EQUAL(fileExists(newFile + ".txt"), true);

    /**
     * Create file that already exists and read
     * from it to make sure it wasn't modified
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = existingFile;
    fsman->create(fres);
    PRINT("create file with existing filename");
    PRINT("    " <<existingFile <<".txt");
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = existingFile;
    fsman->read(fres);
    PRINT("read existing filename");
    PRINT("    " <<fres->content);
    PRINT("hex print of fres->content");
    hexPrint(fres->content.c_str());
    PRINT("hex print of testExistingString");
    hexPrint(testExistingString.c_str());
    ASSERT_STRING_EQUAL(testExistingString, fres->content);

    /**
     * Read file with wrong filename
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = wrongFile;
    fsman->read(fres);
    PRINT("read file with wrong filename");
    PRINT("    " <<fres->content);
    ASSERT_STRING_EQUAL(testEmptyString, fres->content);

    /**
     * Read newly created file
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fres->content = testDirtyString;
    fsman->read(fres);
    PRINT("read newly created file");
    PRINT("    " <<fres->content);
    ASSERT_STRING_EQUAL(testEmptyString, fres->content);

    /**
     * Update file with wrong filename
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = wrongFile;
    fsman->update(fres);
    PRINT("update file with wrong filename");
    PRINT("    " <<wrongFile <<".txt");
    ASSERT_EQUAL(fileExists(wrongFile + ".txt"), false);

    /**
     * Update new file with new string
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fres->content = testNewString;
    fsman->update(fres);
    PRINT("update new file with new string");
    PRINT("    " <<testNewString);
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fsman->read(fres);
    PRINT("read new file");
    PRINT("    " <<fres->content);
    PRINT("hex print of fres->content");
    hexPrint(fres->content.c_str());
    PRINT("hex print of testNewString");
    hexPrint(testNewString.c_str());
    ASSERT_STRING_EQUAL(testNewString, fres->content);

    /**
     * Update new file with empty string
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fres->content = testEmptyString;
    fsman->update(fres);
    PRINT("update new file with empty string");
    PRINT("    " <<testEmptyString);
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fsman->read(fres);
    PRINT("read new file");
    PRINT("    " <<fres->content);
    ASSERT_STRING_EQUAL(testEmptyString, fres->content);

    /**
     * remove new file
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = newFile;
    fsman->remove(fres);
    PRINT("remove new file");
    PRINT("    " <<newFile <<".txt");
    ASSERT_EQUAL(fileExists(newFile + ".txt"), false);

    PRINT("   --------------------   ");
    /**
     * Concurrency test: launch N threads that will storm the log
     *
     * TODO
     */

    /**
     * Start THD_NUM threads successfully
     *
     * Expected value: for() exist when thd_idx == THD_NUM
     */
    stubMng = new StubFSManager();

    stringstream strStream;
    strStream.str(string());
    pthread_t fsThread[THD_NUM];
    int thd_idx;
    for (thd_idx = 0; thd_idx < THD_NUM; thd_idx++){
        int *idx = new int;
        *idx = thd_idx;
        if (pthread_create(&fsThread[thd_idx], 0, fs_bombing_function, (void*) idx) < 0)
            break;
        strStream <<"thread " <<thd_idx <<" has started";
        //PRINT(strStream.str());
    }
    PRINT("start THD_NUM threads successfully");
    ASSERT_EQUAL(thd_idx, THD_NUM);

    /**
     * Join all launched threads
     */
    strStream.str(string());
    int thd_jn;
    for (thd_jn = 0; thd_jn < thd_idx; thd_jn++){
        if (pthread_join(fsThread[thd_jn], 0) < 0)
            break;
        strStream <<"thread " <<thd_jn <<" has joined";
        //PRINT(strStream.str());
    }
    PRINT("join all started threads");
    ASSERT_EQUAL(thd_jn, thd_idx);

    delete stubMng;
    return 0;
}
