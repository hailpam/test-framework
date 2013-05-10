#include <rawfsmanager.h>
#include <debug.h>
#include <string>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;
using namespace it::testbench::ioutil;

/**
 * Check if file exists
 */
bool fileExists(const string filename);

/**
 * Clean resources
 */
void clearRes(FormattedResource *fres){
    fres->ext.clear();
    fres->content.clear();
    fres->name.clear();
    fres->hash.clear();
}

int main(int argc, char *argv[]){
    /**
     * Setup: prepare string
     */
    string testExistingString = "This is a known string";
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
    ASSERT_EQUAL(testExistingString, fres->content);

    /**
     * Read file with wrong filename
     */
    clearRes(fres);
    fres->ext = fileTxt;
    fres->name = wrongFile;
    fsman->read(fres);
    PRINT("read file with wrong filename");
    PRINT("    " <<fres->content);
    ASSERT_EQUAL(testEmptyString, fres->content);

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
    ASSERT_EQUAL(testEmptyString, fres->content);

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
    ASSERT_EQUAL(testNewString, fres->content);

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
    ASSERT_EQUAL(testEmptyString, fres->content);

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
}
