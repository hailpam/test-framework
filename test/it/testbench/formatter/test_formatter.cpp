#include <list>
#include <support.h>
#include <formatter_manager.h>

using namespace std;
using namespace it::testbench::formatter;

int main(int argc, char *argv[]){
	PRINT("Test Formatter package");
	// set report identifiers
	string sId = "MySessionId";
	string tpId = "MyTestPlanId";
	Report *report = new Report;
	report->setSessionId(&sId);
	report->setTestPlanId(&tpId);
	report->setTestId(1234);
	// set list of return codes
	PRINT("Set list of return codes");
	list<ReturnCode*> retCodes;
	ReturnCode *rc01, *rc02, *rc03;
	rc01 = new ReturnCode();
	rc01->code = SUCCESS;
	rc01->desc = "MyTestItem01";
	retCodes.push_back(rc01);
	rc02 = new ReturnCode();
	rc02->code = ERROR;
	rc02->desc = "MyTestItem02";
	retCodes.push_back(rc02);
    rc02 = new ReturnCode();
	rc02->code = SUCCESS;
	rc02->desc = "MyTestItem03";
	retCodes.push_back(rc03);
	report->setOutcome(&retCodes);
	// set console resource format
	PRINT("Set console resource format");
	ConsoleResource *cres = new ConsoleResource;
	cres->lineSeparator = '-';
	cres->columnSeparator = '|';
	cres->tabSpaces = 2;
	cres->valBracket = '[';
	cres->beautify = true;
	report->setConsoleResource(cres);
	// format
	PRINT("Format");
	FormatterManager fmtManager;
	try {
        ReturnCode retCode = fmtManager.formatForConsole(report);
	} catch (exception &ex) {
        PRINT("formatForConsole failed!!!");
        return -1;
	}
	PRINT(cres->content);
	return 0;
}
