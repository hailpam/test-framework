#include <formatter_functor.h>
#include <formatter_util.h>

namespace it
{
namespace testbench
{
namespace formatter
{

/**
 * Macros for tag formatting
 */
#define XML_BEGIN_TAG(a) \
    { fres->content += beginMarkup; \
    fres->content += (a); }

#define XML_END_TAG() \
    { fres->content += endMarkup; \
    fres->content += newLine; }

#define XML_END_CLOSE_TAG(a) \
    { fres->content += spaceStr; \
    fres->content += (a); \
    fres->content += endMarkup; \
    fres->content += newLine; }

#define XML_TAG_PAIR(a, b) \
    { fres->content += spaceStr; \
    fres->content += (a); \
    fres->content += equalStr; \
    fres->content += quoteStr; \
    fres->content += (b); \
    fres->content += quoteStr; }

#define XML_CLOSE_TAG(a) \
    { fres->content += beginMarkup; \
    fres->content += closeMarkup; \
    fres->content += (a); \
    fres->content += endMarkup; \
    fres->content += newLine; }

const char XML_BEGIN_MARKUP = '<';    /* default char for marking up the beginning of a tag */
const char XML_END_MARKUP = '>';      /* default char for marking up the end of a tag */
const char XML_CLOSE_MARKUP = '/';    /* default char for marking up a closing tag */
const char XML_QUOTE = '\"';          /* default char for quote */
const char XML_EQUAL = '=';           /* default char for equal */

XmlFunctor::XmlFunctor(){
    tabSep = BLANK_SPACE;
    tabSep = indent(tabSep, TAB_SPACES);
    newLine = NEW_LINE;
    beginMarkup = XML_BEGIN_MARKUP;
    endMarkup = XML_END_MARKUP;
    closeMarkup = XML_CLOSE_MARKUP;
    spaceStr = BLANK_SPACE;
    quoteStr = XML_QUOTE;
    equalStr = XML_EQUAL;
}

XmlFunctor::~XmlFunctor() {/* do nothing here*/}

ReturnCode XmlFunctor::format(Report *report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode ret;
    ret.code = SUCCESS;
    ret.desc = "Content formatted for XML file successfully";
    // Get Formatted Resource
    DEBUG("Get Formatted Resource");
    FormattedResource *fres = report->getFormattedResource();
    if (!fres) {
        throw TestFrameworkException("Null Pointer passed as Formatted Resource");
    }
    fres->content = "";
    // XML Header tag
    XML_BEGIN_TAG("?xml");
    XML_TAG_PAIR("version", "1.0");
    XML_END_CLOSE_TAG("?");
    // TestBenchConfiguration tag open
    DEBUG("TestBenchConfiguration tag open");
    XML_BEGIN_TAG("TestBenchConfiguration");
    XML_TAG_PAIR("name", "SessionId");
    XML_TAG_PAIR("value", *(report->getSessionId()));
    XML_END_TAG();
    // TestPlan tag open
    DEBUG("TestPlan tag open");
    fres->content += indent(tabSep, 1);
    XML_BEGIN_TAG("TestPlan");
    XML_TAG_PAIR("name", "TestPlanId");
    XML_TAG_PAIR("value", *(report->getTestPlanId()));
    XML_END_TAG();
    // TestCase tag open
    DEBUG("TestCase tag open");
    fres->content += indent(tabSep, 2);
    XML_BEGIN_TAG("TestCase");
    XML_TAG_PAIR("name", "TestId");
    XML_TAG_PAIR("value", intToStr(report->getTestId()));
    XML_END_TAG();
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
        // TestItem tag open
        DEBUG("TestItem tag open");
        fres->content += indent(tabSep, 3);
        XML_BEGIN_TAG("TestItem");
        XML_TAG_PAIR("name", "TestItemId");
        XML_TAG_PAIR("value", intToStr(tiCounter + 1));
        XML_END_TAG();
        // TestItem result tag
        DEBUG("TestItem result line");
        fres->content += indent(tabSep, 4);
        XML_BEGIN_TAG("Result");
        XML_TAG_PAIR("code", resultCode(retCode));
        XML_TAG_PAIR("description", retCode->desc);
        XML_END_CLOSE_TAG(closeMarkup);
        // TestItem tag close
        fres->content += indent(tabSep, 3);
        XML_CLOSE_TAG("TestItem");
    }
    // TestCase tag close
    DEBUG("TestCase tag close");
    fres->content += indent(tabSep, 2);
    XML_CLOSE_TAG("TestCase");
    // TestPlan tag close
    DEBUG("TestPlan tag close");
    fres->content += indent(tabSep, 1);
    XML_CLOSE_TAG("TestPlan");
    // TestBenchConfiguration tag close
    DEBUG("TestBenchConfiguration tag close");
    XML_CLOSE_TAG("TestBenchConfiguration");
    return ret;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
