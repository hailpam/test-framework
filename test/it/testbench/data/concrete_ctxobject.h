#ifndef CONCRETE_CTXOBJECT_H
#define CONCRETE_CTXOBJECT_H


#include <testitem.h>

namespace it
{
namespace testbench
{
namespace data
{

class A {
    public:
        A();
        string getAString();
    private:
        string aString;
};

class B {
    public:
        B();
        string getBString();
    private:
        string bString;
};

class ConcreteContextObject: public TestCaseContext {
    public:
        ConcreteContextObject();
        ~ConcreteContextObject();
        void setDescription(const string& description);
        const string& getDescription() const;
        A* getA();
        B* getB();
        void setA(A* aVar);
        void setB(B* bVar);
    private:
        A* a;
        B* b;
};

} /* DATA */
} /* TESTBENCH */
} /* IT */

#endif /* CONCRETE_CTXOBJECT_H */
