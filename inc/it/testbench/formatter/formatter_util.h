#ifndef FORMATTER_UTIL_H
#define FORMATTER_UTIL_H

#include <string>
#include <sstream>
#include <debug.h>

namespace it
{
namespace testbench
{
namespace formatter
{

/**
 * Global constants
 */
const char BLANK_SPACE = ' ';      /* default char for blank space */
const char NEW_LINE = '\n';        /* default char for new line */
const unsigned int TAB_SPACES = 4; /* default number of tab spaces for indentation */

/**
 * Helper functions
 */
inline string resultCode(const ReturnCode *ret){
    if (!ret)
        return "NULL POINTER";
    else if (ret->code == SUCCESS)
        return "SUCCESS";
    else if (ret->code == ERROR)
        return "ERROR";
    else
        return "INVALID RETURN CODE";
}

inline string indent(const string tabs, unsigned int level){
    string retTabs = "";
    while (level--)
        retTabs += tabs;
    return retTabs;
}

inline string intToStr(const unsigned int num){
    stringstream i2s;
    i2s.str(string());
    i2s <<num;
    return i2s.str();
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */

#endif /* FORMATTER_UTIL_H */
