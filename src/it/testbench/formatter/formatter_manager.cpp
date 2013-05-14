#include <formatter_manager.h>
#include <debug.h>

namespace it
{
namespace testbench
{
namespace formatter
{

FormatterManager::FormatterManager(){
    DEBUG("");
    /*
    CsvFunctor *csvFunctor = new CsvFunctor();
    fmtFunctor["csv"] = static_cast<FormatterFunctor*>(csvFunctor);
    JsonFunctor *jsonFunctor = new JsonFunctor();
    fmtFunctor["json"] = static_cast<FormatterFunctor*>(jsonFunctor);
    TxtFunctor *txtFunctor = new TxtFunctor();
    fmtFunctor["txt"] = static_cast<FormatterFunctor*>(txtFunctor);
    XmlFunctor *xmlFunctor = new XmlFunctor();
    fmtFunctor["xml"] = static_cast<FormatterFunctor*>(xmlFunctor);
    */
    cslFunctor = new ConsoleFunctor();
}

FormatterManager::~FormatterManager(){
    DEBUG("");
    /*
    delete fmtFunctor["csv"];
    delete fmtFunctor["json"];
    delete fmtFunctor["txt"];
    delete fmtFunctor["xml"];
    */
    delete cslFunctor;
}

ReturnCode FormatterManager::formatForConsole(Report* report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode retCode;
    try {
        retCode = cslFunctor->format(report);
    } catch (exception &ex) {
        throw ex;
    }
    return retCode;
}

ReturnCode FormatterManager::formatForFile(Report* report) throw (TestFrameworkException){
    DEBUG("");
    ReturnCode retCode;
    string ext = report->getFormattedResource()->ext;
    if (fmtFunctor.count(ext)) {
        try {
            retCode = fmtFunctor[ext]->format(report);
        } catch (exception &ex) {
            throw ex;
        }
    } else {
        throw TestFrameworkException("Invalid file extension");
    }
    return retCode;
}

} /* FORMATTER */
} /* TESTBENCH */
} /* IT */
