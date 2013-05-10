#include "test_stubfsmanager.h"

using namespace std;
using namespace it::testbench::ioutil;

/**
 * Init mutex, and start with no file
 */
StubFSManager::StubFSManager() {
    if (pthread_mutex_init(&fsMux, 0) < 0)
        return;
    fsState.clear();
    fileCreated = false;
};

/**
 * Destroy mutex
 */
StubFSManager::~StubFSManager() {
    pthread_mutex_destroy(&fsMux);
};

/**
 * Only if file is not present, set it as created and
 * put content as empty
 */
void StubFSManager::create(const FormattedResource *fres){
    if (pthread_mutex_lock(&fsMux) < 0)
        return;
    if (!fileCreated){
        fileCreated = true;
        fsState.clear();
    }
    pthread_mutex_unlock(&fsMux);
};

/**
 *Only if file is present, return the content
 */
void StubFSManager::read(FormattedResource *fres){
    if (pthread_mutex_lock(&fsMux) < 0)
        return;
    if (fileCreated)
        fres->content = fsState;
    pthread_mutex_unlock(&fsMux);
};

/**
 * Only if file is present, overwrite the content
 */
void StubFSManager::update(const FormattedResource *fres){
    if (pthread_mutex_lock(&fsMux) < 0)
        return;
    if (fileCreated)
        fsState = fres->content;
    pthread_mutex_unlock(&fsMux);
};

/**
 * Only if file is present, set it as not created
 */
void StubFSManager::remove(const FormattedResource* fres){
    if (pthread_mutex_lock(&fsMux) < 0)
        return;
    if (fileCreated)
        fileCreated = false;
    pthread_mutex_unlock(&fsMux);
};
