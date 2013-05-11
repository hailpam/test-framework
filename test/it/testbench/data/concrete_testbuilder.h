#ifndef CONCRETE_TESTBUILDER_H
#define CONCRETE_TESTBUILDER_H

#include <testbench.h>
#include <custom_testitems.h>

namespace it
{
namespace testbench
{
namespace data
{

class TestCaseBuilder1 : public TestCaseBuilder {

    public:
        TestCaseBuilder1();
        ~TestCaseBuilder1();
        TestCase* buildTestCase();

};

class TestCaseBuilder2 : public TestCaseBuilder {

    public:
        TestCaseBuilder2();
        ~TestCaseBuilder2();
        TestCase* buildTestCase();

};

class TestCaseBuilder3 : public TestCaseBuilder {

    public:
        TestCaseBuilder3();
        ~TestCaseBuilder3();
        TestCase* buildTestCase();

};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* CONCRETE_TESTBUILDER_H */
