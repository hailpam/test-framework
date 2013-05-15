#include <sstream>
#include <list>
#include <formatter_functor.h>
#include <debug.h>
#include <formatter_util.h>

namespace it
{
namespace testbench
{
namespace formatter
{

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
    if (!cres) {
        throw TestFrameworkException("Null Pointer passed as Console Resource");
    }
    lineSep = cres->lineSeparator;
    columnSep = cres->columnSeparator;
    unsigned int tabSpaces = cres->tabSpaces;
    tabSep = BLANK_SPACE;
    newLine.clear();
    openPar.clear();
    closePar.clear();
    if (cres->beautify){
        tabSep = indent(tabSep, tabSpaces);
        newLine = NEW_LINE;
        openPar = cres->valBracket;
        if ( (cres->valBracket == '<') || (cres->valBracket == '[') || (cres->valBracket == '{') )
            closePar = cres->valBracket + 2;
        else if (cres->valBracket == '(')
            closePar = cres->valBracket + 1;
        else
            closePar = cres->valBracket;
    }
    cres->content = "";
    // TestBenchConfiguration line
    DEBUG("TestBenchConfiguration line");
    //cres->content += "Testbench Configuration ";
    //cres->content += lineSep;
    cres->content += "Session Id: ";
    cres->content += lineSep;
    cres->content += openPar;
    cres->content += *(report->getSessionId());
    cres->content += closePar;
    cres->content += columnSep;
    cres->content += newLine;
    // TestPlan line
    DEBUG("TestPlan line");
    cres->content += indent(tabSep, 1);
    cres->content += "Test Plan: ";
    cres->content += lineSep;
    cres->content += openPar;
    cres->content += *(report->getTestPlanId());
    cres->content += closePar;
    cres->content += columnSep;
    cres->content += newLine;
    // TestCase line
    DEBUG("TestCase line");
    cres->content += indent(tabSep, 2);
    cres->content += "Test Case n: ";
    cres->content += lineSep;
    cres->content += openPar;
    cres->content += intToStr(report->getTestId());
    cres->content += closePar;
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
        cres->content += openPar;
        cres->content += intToStr(tiCounter + 1);
        cres->content += closePar;
        cres->content += columnSep;
        cres->content += newLine;
        // TestItem result line
        DEBUG("TestItem result line");
        cres->content += indent(tabSep, 4);
        cres->content += "Result: ";
        cres->content += openPar;
        cres->content += resultCode(retCode);
        cres->content += closePar;
        cres->content += columnSep;
        cres->content += newLine;
        // TestItem description line
        DEBUG("TestItem description line");
        cres->content += indent(tabSep, 4);
        cres->content += openPar;
        cres->content += retCode->desc;
        cres->content += closePar;
        cres->content += columnSep;
        cres->content += newLine;
    }
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
