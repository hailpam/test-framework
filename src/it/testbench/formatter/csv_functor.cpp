#include <formatter_functor.h>
#include <formatter_util.h>

namespace it
{
namespace testbench
{
namespace formatter
{

/**
 * CSV-specific constants
 */
const char CSV_COMMA = ',';        /* default char for comma in CSV format */
const string CSV_QUOTE = "\"";        /* default char for quote in CSV format */

CsvFunctor::CsvFunctor(){
        commaStr = CSV_COMMA;
        quoteStr = CSV_QUOTE;
        newLine = NEW_LINE;
}

CsvFunctor::~CsvFunctor() {/* do nothing here*/}

ReturnCode CsvFunctor::format(Report *report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode ret;
    ret.code = SUCCESS;
    ret.desc = "Content formatted for CSV file successfully";
    // Define special chars to be used for formatting
    DEBUG("Get Formatted Resource");
    FormattedResource *fres = report->getFormattedResource();
    if (!fres) {
        throw TestFrameworkException("Null Pointer passed as Formatted Resource");
    }
    fres->content = "";
    // Write header line
    DEBUG("Write header line");
    //// TestBench Configuraion
    fres->content += quoteStr;
    fres->content += "Session Id";
    fres->content += quoteStr;
    fres->content += commaStr;
    //// TestPlan
    fres->content += quoteStr;
    fres->content += "Test Plan Id";
    fres->content += quoteStr;
    fres->content += commaStr;
    //// TestCase
    fres->content += quoteStr;
    fres->content += "Test Case Id";
    fres->content += quoteStr;
    fres->content += commaStr;
    //// TestItem
    fres->content += quoteStr;
    fres->content += "Test Item Id";
    fres->content += quoteStr;
    fres->content += commaStr;
    //// TestItem result
    fres->content += quoteStr;
    fres->content += "Test Item result code";
    fres->content += quoteStr;
    fres->content += commaStr;
    //// TestItem description
    fres->content += quoteStr;
    fres->content += "Test Item result description";
    fres->content += quoteStr;
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
        // TestBenchConfiguration
        DEBUG("TestBenchConfiguration");
        fres->content += quoteStr;
        fres->content += *(report->getSessionId());
        fres->content += quoteStr;
        fres->content += commaStr;
        // TestPlan
        DEBUG("TestPlan");
        fres->content += quoteStr;
        fres->content += *(report->getTestPlanId());
        fres->content += quoteStr;
        fres->content += commaStr;
        // TestCase
        DEBUG("TestCase");
        fres->content += quoteStr;
        fres->content += intToStr(report->getTestId());
        fres->content += quoteStr;
        fres->content += commaStr;
        // TestItem
        DEBUG("TestItem");
        fres->content += quoteStr;
        fres->content += intToStr(tiCounter + 1);
        fres->content += quoteStr;
        fres->content += commaStr;
        // TestItem result
        DEBUG("TestItem result");
        fres->content += quoteStr;
        fres->content += resultCode(retCode);
        fres->content += quoteStr;
        fres->content += commaStr;
        // TestItem description
        DEBUG("TestItem description");
        fres->content += quoteStr;
        fres->content += retCode->desc;
        fres->content += quoteStr;
        fres->content += newLine;
    }
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
