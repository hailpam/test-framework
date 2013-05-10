#include <fstream>
#include <sys/stat.h>
#include <cstdio>

#include <rawfsmanager.h>
#include <debug.h>
#include <sstream>

using namespace std;
using namespace it::testbench::ioutil;

RawFSManager* RawFSManager::instance = 0; /*!< static pointer to ensure a single instance */
fstream RawFSManager::fs;          /*!< File stream used for log file */
pthread_mutex_t RawFSManager::fsMux = PTHREAD_MUTEX_INITIALIZER;  /*!< mutex for protecting static variables */

const int BUF_SIZE = 4096;

RawFSManager::RawFSManager(){
    DEBUG("");
    /* Follow a lazy initialization strategy, do nothing here */
}

RawFSManager::~RawFSManager(){
    DEBUG("");
    /* Do nothing here */
}

RawFSManager* RawFSManager::getInstance(){
    DEBUG("");
    if (!instance)
        instance = new RawFSManager();
    return instance;
}

/**
 * Helper functions
 */

bool invalidRes(const FormattedResource *fres){
    stringstream strStream;
    strStream <<"ext.length = " <<fres->ext.length() <<" name.length() = " <<fres->name.length();
    DEBUG(strStream.str());
    return ( !fres->ext.length() || !fres->name.length() );
}

/**
 * Gets the complete file name, in the format name.ext, from
 * the FormattedResource
 */
inline string stringName(const FormattedResource *fres){
    string fileName = fres->name + ".";
    fileName += fres->ext;
    DEBUG("file name is " <<fileName);
    return fileName;
}

/**
 * Check if file exists
 */
bool fileExists(const string filename){
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1) {
        DEBUG("file " <<filename <<" exists");
        return true;
    }
    DEBUG("file " <<filename <<" doesn't exist");
    return false;
}

/**
 * Provisional implementation will sychronize on one
 * filestream for each file.
 *
 * TODO: create a map of <string, mutex, fstream> that
 * uses a mutex and a fstream for each single file to
 * parallelize and speed up
 *
 * TODO: dual-threaded buffered I/O (currently it's
 * single-threaded)
 */

void RawFSManager::create(const FormattedResource *fres){
    DEBUG("");
    /* sanity check first */
    if (!instance)
        return; // exception
    if (invalidRes(fres))
        return; // exception
    string fileName = stringName(fres);
    if (fileExists(fileName))
        return; // exception
    /* lockRes() - acquire mutex on fstream */
    if (pthread_mutex_lock(&fsMux) < 0)
        return; // exception
    DEBUG("mutex acquired");
    /* create file */
    if (!fs.is_open()) { // exception
        fs.open(fileName.c_str(), std::fstream::out);
        if (!fs.fail()){ //exception
            DEBUG("fstream opened");
            fs.close();
        }
    }
    /* unlockRes() - release mutex */
    pthread_mutex_unlock(&fsMux);
    DEBUG("mutex released");
}

void RawFSManager::read(FormattedResource *fres){
    DEBUG("");
    /* sanity check first */
    if (!instance)
        return; // exception
    if (invalidRes(fres))
        return; // exception
    string fileName = stringName(fres);
    if (!fileExists(fileName))
        return; // exception
    /* lockRes() - acquire mutex on fstream */
    if (pthread_mutex_lock(&fsMux) < 0)
        return; // exception
    /* read file */
    if (!fs.is_open()) { // exception
        fs.open(fileName.c_str(), std::fstream::in);
        if (!fs.fail()) { //exception
            char buffer[BUF_SIZE];
            fres->content.clear();
            while (!fs.eof()) {
                fs.read(buffer, sizeof(buffer));
                fres->content += buffer;
            }
            fs.close();
        }
    }
    /* unlockRes() - release mutex */
    pthread_mutex_unlock(&fsMux);
}

void RawFSManager::update(const FormattedResource *fres){
    DEBUG("");
    /* sanity check first */
    if (!instance)
        return; // exception
    if (invalidRes(fres))
        return; // exception
    string fileName = stringName(fres);
    if (!fileExists(fileName))
        return; // exception
    /* lockRes() - acquire mutex on fstream */
    if (pthread_mutex_lock(&fsMux) < 0)
        return; // exception
    /* write file */
    if (!fs.is_open()) { // exception
        fs.open(fileName.c_str(), std::fstream::out | std::fstream::trunc);
        if (!fs.fail()) { //exception
            char buffer[BUF_SIZE];
            size_t read_bytes, pos = 0, len_bytes = fres->content.length();
            while (len_bytes) {
                read_bytes = fres->content.copy(buffer, sizeof(buffer), pos);
                len_bytes -= read_bytes;
                pos += read_bytes;
                fs.write(buffer, read_bytes);
            }
            fs.flush();
            fs.close();
        }
    }
    /* unlockRes() - release mutex */
    pthread_mutex_unlock(&fsMux);
}

void RawFSManager::remove(const FormattedResource* fres){
    DEBUG("");
/* sanity check first */
    if (!instance)
        return; // exception
    if (invalidRes(fres))
        return; // exception
    string fileName = stringName(fres);
    if (!fileExists(fileName))
        return; // exception
    /* lockRes() - acquire mutex on fstream */
    if (pthread_mutex_lock(&fsMux) < 0)
        return; // exception
    std::remove(fileName.c_str());
    /* unlockRes() - release mutex */
    pthread_mutex_unlock(&fsMux);
}
