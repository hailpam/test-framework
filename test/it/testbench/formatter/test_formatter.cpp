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
        rc03 = new ReturnCode();
	rc03->code = SUCCESS;
	rc03->desc = "MyTestItem03";
	retCodes.push_back(rc03);
	report->setOutcome(&retCodes);
        // create objects
        FormatterManager fmtManager;
	ConsoleResource *cres = new ConsoleResource;
	report->setConsoleResource(cres);
        FormattedResource *fres = new FormattedResource;
	report->setFormattedResource(fres);
	// 1: format for console
        PRINT("Set console resource format");
	cres->lineSeparator = '-';
	cres->columnSeparator = '|';
	cres->tabSpaces = 2;
	cres->valBracket = '[';
	cres->beautify = true;
	PRINT(">> Format for console");
	try {
            ReturnCode retCode = fmtManager.formatForConsole(report);
            PRINT(cres->content);
	} catch (exception &ex) {
            PRINT("formatForConsole failed!!!");
	}
        // 2: format for TXT file
	PRINT(">> Format for TXT file");
        fres->ext = "txt";
	try {
            ReturnCode retCode = fmtManager.formatForFile(report);
            PRINT(fres->content);
	} catch (exception &ex) {
            PRINT("formatForFile in TXT failed!!!");
	}
        // 3: format for CSV file
	PRINT(">> Format for CSV file");
        fres->ext = "csv";
	try {
            ReturnCode retCode = fmtManager.formatForFile(report);
            PRINT(fres->content);
	} catch (exception &ex) {
            PRINT("formatForFile in CSV failed!!!");
	}
        // 4: format for JSON file
	PRINT(">> Format for JSON file");
        fres->ext = "json";
	try {
            ReturnCode retCode = fmtManager.formatForFile(report);
            PRINT(fres->content);
	} catch (exception &ex) {
            PRINT("formatForFile in JSON failed!!!");
	}
	return 0;
}
