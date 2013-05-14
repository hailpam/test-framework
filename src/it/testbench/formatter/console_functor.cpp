#include <sstream>
#include <list>
#include <formatter_functor.h>
#include <debug.h>

namespace it
{
namespace testbench
{
namespace formatter
{

/**
 * Helper functions
 */
inline string resultCode(const ReturnCode *ret){
    if (ret->code == SUCCESS)
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

ConsoleFunctor::ConsoleFunctor() {
    DEBUG("");
}

ConsoleFunctor::~ConsoleFunctor() {
    DEBUG("");
}

ReturnCode ConsoleFunctor::format(Report *report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode ret;
    ret.code = SUCCESS;
    ret.desc = "Content formatted for console successfully";
    // Define special chars to be used for formatting
    DEBUG("Get Console Resource");
    ConsoleResource *cres = report->getConsoleResource();
    PRINT("Got Console Resource" <<cres);
    if (!cres) {
        throw TestFrameworkException("Null Pointer passed as Console Resource");
    }
    lineSep = cres->lineSeparator;
    columnSep = cres->columnSeparator;
    unsigned int tabSpaces = cres->tabSpaces;
    tabSep = " ";
    newLine.clear();
    openPar.clear();
    closePar.clear();
    if (cres->beautify){
        tabSep = indent(tabSep, tabSpaces);
        newLine = '\n';
        openPar = cres->valBracket;
        closePar = cres->valBracket + 1;
    }
    cres->content = "";
    // TestBenchConfiguration line
    DEBUG("TestBenchConfiguration line");
    cres->content += "Testbench Configuration ";
    cres->content += lineSep;
    cres->content += "Session Id ";
    cres->content += lineSep;
    cres->content += *(report->getSessionId());
    cres->content += columnSep;
    cres->content += newLine;
    // TestPlan line
    DEBUG("TestPlan line");
    cres->content += indent(tabSep, 1);
    cres->content += "Test Plan ";
    cres->content += lineSep;
    cres->content += *(report->getTestPlanId());
    cres->content += columnSep;
    cres->content += newLine;
    // TestCase line
    DEBUG("TestCase line");
    cres->content += indent(tabSep, 2);
    cres->content += "Test Case n: ";
    cres->content += lineSep;
    cres->content += intToStr(report->getTestId());
    cres->content += columnSep;
    cres->content += newLine;
    // prepare cycle for processing Test Items
    DEBUG("Prepare cycle for processing Test Items");
    list<ReturnCode*> *listRetCodes = report->getOutcome();
    if (!listRetCodes){
        throw TestFrameworkException("Null Pointer passed as list of Return Codes");
    }
    list<ReturnCode*>::iterator itrRetCode;
    unsigned int tiCounter;
    for (itrRetCode = listRetCodes->begin(), tiCounter = 0; tiCounter < listRetCodes->size(); itrRetCode++, tiCounter++) {
        ReturnCode *retCode = (*itrRetCode);
        // TestItem line
        DEBUG("TestItem line");
        cres->content += indent(tabSep, 3);
        cres->content += "Test Item ";
        cres->content += intToStr(++tiCounter);
        cres->content += columnSep;
        cres->content += newLine;
        // TestItem result line
        DEBUG("TestItem result line");
        cres->content += indent(tabSep, 4);
        cres->content += "Result: ";
        cres->content += resultCode(retCode);
        cres->content += columnSep;
        cres->content += newLine;
        // TestItem description line
        DEBUG("TestItem description line");
        cres->content += indent(tabSep, 4);
        cres->content += retCode->desc;
        cres->content += columnSep;
        cres->content += newLine;
    }
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
