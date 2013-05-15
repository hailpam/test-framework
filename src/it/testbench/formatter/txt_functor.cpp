#include <formatter_functor.h>
#include <formatter_util.h>

namespace it
{
namespace testbench
{
namespace formatter
{

TxtFunctor::TxtFunctor(){
        tabSep = BLANK_SPACE;
	tabSep = indent(tabSep, TAB_SPACES);
        newLine = NEW_LINE;
}

TxtFunctor::~TxtFunctor() {/* do nothing here*/}

ReturnCode TxtFunctor::format(Report *report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode ret;
    ret.code = SUCCESS;
    ret.desc = "Content formatted for TXT file successfully";
    // Define special chars to be used for formatting
    DEBUG("Get Formatted Resource");
    FormattedResource *fres = report->getFormattedResource();
    if (!fres) {
        throw TestFrameworkException("Null Pointer passed as Formatted Resource");
    }
    fres->content = "";
    // TestBenchConfiguration line
    DEBUG("TestBenchConfiguration line");
    //fres->content += "Testbench Configuration ";
    fres->content += "Session Id: ";
    fres->content += *(report->getSessionId());
    fres->content += newLine;
    // TestPlan line
    DEBUG("TestPlan line");
    fres->content += indent(tabSep, 1);
    fres->content += "Test Plan: ";
    fres->content += *(report->getTestPlanId());
    fres->content += newLine;
    // TestCase line
    DEBUG("TestCase line");
    fres->content += indent(tabSep, 2);
    fres->content += "Test Case n: ";
    fres->content += intToStr(report->getTestId());
    fres->content += newLine;
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
        fres->content += indent(tabSep, 3);
        fres->content += "Test Item ";
        fres->content += intToStr(tiCounter + 1);
        fres->content += newLine;
        // TestItem result line
        DEBUG("TestItem result line");
        fres->content += indent(tabSep, 4);
        fres->content += "Result: ";
        fres->content += resultCode(retCode);
        fres->content += newLine;
        // TestItem description line
        DEBUG("TestItem description line");
        fres->content += indent(tabSep, 4);
        fres->content += retCode->desc;
        fres->content += newLine;
    }
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
