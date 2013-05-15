#ifndef FORMATTER_FUNCTOR_H
#define FORMATTER_FUNCTOR_H

#include <support.h>

// $Id$
/**
 * @file formatter_functor.h
 * This module defines the Formatter Functor and its specializations,
 * that shall format the incoming Report in several different formats:
 * raw text for console, raw text for TXT file, CSV, XML and JSON
 *
 * @brief

 *
 * @author Raffaele Aquilone <aquiloneraf@gmail.com>
 * @version 0.1
 */
// $Log$

///  Single line comment for dOxygen.

using namespace std;
using namespace it::testbench::data;

namespace it
{
namespace testbench
{
namespace formatter
{

/*!
 * Base abstract class FormatterFunctor that provides just one method
 * to format Reports. Its specializations shall implement a particular
 * format and be aimed at a particular output device (console or file).
 */
class FormatterFunctor {
    public:
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        virtual ReturnCode format(Report *report) throw (TestFrameworkException) = 0;    /*!< format report */
};

/*!
 * Functor for console output
 */
class ConsoleFunctor : public FormatterFunctor {
    public:
        ConsoleFunctor();
        virtual ~ConsoleFunctor();
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode format(Report *report) throw (TestFrameworkException);        /*!< format report */
    private:
        string lineSep;               /*!< line separator character */
        string columnSep;             /*!< column separator character */
        string tabSep;                /*!< string of tab spaces for indentation */
        string openPar;               /*!< open parentheses character */
        string closePar;              /*!< close parentheses character */
        string newLine;               /*!< new line character */
};

/*!
 * Functor for TXT file output
 */
class TxtFunctor : public FormatterFunctor {
    public:
        TxtFunctor();
        virtual ~TxtFunctor();
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode format(Report *report) throw (TestFrameworkException);        /*!< format report */
    private:
        string tabSep;              /*!< string of tab spaces for indentation */
        string newLine;             /*!< new line character */
};

/*!
 * Functor for CSV file output
 */
class CsvFunctor : public FormatterFunctor {
    public:
        CsvFunctor();
        virtual ~CsvFunctor();
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode format(Report *report) throw (TestFrameworkException);        /*!< format report */
    private:
        string commaStr;            /*!< comma character */
        string quoteStr;            /*!< quote character */
        string newLine;             /*!< new line character */
};

/*!
 * Functor for XML file output
 */
class XmlFunctor : public FormatterFunctor {
    public:
        XmlFunctor();
        virtual ~XmlFunctor();
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode format(Report *report) throw (TestFrameworkException);        /*!< format report */
};

/*!
 * Functor for JSON file output
 */
class JsonFunctor : public FormatterFunctor {
    public:
        JsonFunctor();
        virtual ~JsonFunctor();
        /**
         * Format a report
         *
         * @param[inout] A report to format
         * @return       Return code describing the outcome of the operation
         */
        ReturnCode format(Report *report) throw (TestFrameworkException);        /*!< format report */
};

} /* IT */
} /* TESTBENCH */
} /* FORMATTER */

#endif /* FORMATTER_FUNCTOR_H */
