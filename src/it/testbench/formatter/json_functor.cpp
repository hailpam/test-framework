#include <formatter_functor.h>
#include <formatter_util.h>

namespace it
{
namespace testbench
{
namespace formatter
{

const char OPEN_BRACKETS = '{';     /* default char for opening brackets */
const char CLOSE_BRACKETS = '}';    /* default char for closing brackets */
const char OPEN_SEQUENCE = '[';     /* default char for opening sequence */
const char CLOSE_SEQUENCE = ']';    /* default char for closing sequence */
const char JSON_COMMA = ',';        /* default char for comma */
const char JSON_COLON = ':';        /* default char for colon */
const char JSON_QUOTE = '\"';       /* default char for quote */

JsonFunctor::JsonFunctor(){
    openField = OPEN_BRACKETS;
    closeField = CLOSE_BRACKETS;
    openSequence = OPEN_SEQUENCE;
    closeSequence = CLOSE_SEQUENCE;
    commaStr = JSON_COMMA;
    colonStr = JSON_COLON;
    quoteStr = JSON_QUOTE;
    tabSep = BLANK_SPACE;
    tabSep = indent(tabSep, TAB_SPACES);
    newLine = NEW_LINE;
}

JsonFunctor::~JsonFunctor() {/* do nothing here*/}

ReturnCode JsonFunctor::format(Report *report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode ret;
    ret.code = SUCCESS;
    ret.desc = "Content formatted for JSON file successfully";
    // Get Formatted Resource
    DEBUG("Get Formatted Resource");
    FormattedResource *fres = report->getFormattedResource();
    if (!fres) {
        throw TestFrameworkException("Null Pointer passed as Formatted Resource");
    }
    fres->content = "";
    // TestBenchConfiguration line
    DEBUG("TestBenchConfiguration line");
    fres->content += openField;
    fres->content += newLine;
    fres->content += indent(tabSep, 1);
    fres->content += quoteStr;
    fres->content += "Session Id";
    fres->content += quoteStr;
    fres->content += colonStr;
    fres->content += quoteStr;
    fres->content += *(report->getSessionId());
    fres->content += quoteStr;
    fres->content += commaStr;
    fres->content += newLine;
    // TestPlan line
    DEBUG("TestPlan line");
    fres->content += indent(tabSep, 1);
    fres->content += quoteStr;
    fres->content += "Test Plan Id";
    fres->content += quoteStr;
    fres->content += colonStr;
    fres->content += quoteStr;
    fres->content += *(report->getTestPlanId());
    fres->content += quoteStr;
    fres->content += commaStr;
    fres->content += newLine;
    // TestCase line
    DEBUG("TestCase line");
    fres->content += indent(tabSep, 1);
    fres->content += quoteStr;
    fres->content += "Test Case Id";
    fres->content += quoteStr;
    fres->content += colonStr;
    fres->content += intToStr(report->getTestId());
    fres->content += commaStr;
    fres->content += newLine;
    // prepare cycle for processing Test Items
    DEBUG("Prepare cycle for processing Test Items");
    fres->content += indent(tabSep, 1);
    fres->content += quoteStr;
    fres->content += "Test Cases";
    fres->content += quoteStr;
    fres->content += colonStr;
    fres->content += openSequence;
    fres->content += newLine;
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
        fres->content += indent(tabSep, 2);
        fres->content += openField;
        fres->content += newLine;
        fres->content += indent(tabSep, 3);
        fres->content += quoteStr;
        fres->content += "Test Item Id";
        fres->content += quoteStr;
        fres->content += colonStr;
        fres->content += intToStr(tiCounter + 1);
        fres->content += commaStr;
        fres->content += newLine;
        // TestItem result line
        DEBUG("TestItem result line");
        fres->content += indent(tabSep, 3);
        fres->content += quoteStr;
        fres->content += "Result";
        fres->content += quoteStr;
        fres->content += colonStr;
        fres->content += quoteStr;
        fres->content += resultCode(retCode);
        fres->content += quoteStr;
        fres->content += commaStr;
        fres->content += newLine;
        // TestItem description line
        DEBUG("Description");
        fres->content += indent(tabSep, 3);
        fres->content += quoteStr;
        fres->content += "Description";
        fres->content += quoteStr;
        fres->content += colonStr;
        fres->content += quoteStr;
        fres->content += retCode->desc;
        fres->content += quoteStr;
        fres->content += newLine;
        fres->content += indent(tabSep, 2);
        fres->content += closeField;
        if (tiCounter + 1 < listRetCodes->size())
            fres->content += commaStr;
        fres->content += newLine;
    }
    fres->content += indent(tabSep, 1);
    fres->content += closeSequence;
    fres->content += newLine;
    fres->content += closeField;
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
