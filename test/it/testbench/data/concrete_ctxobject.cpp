#include <concrete_ctxobject.h>

namespace it
{
namespace testbench
{
namespace data
{

A::A()
{
    aString = "I'm A";
}

string A::getAString()
{
    return aString;
}

B::B()
{
    bString = "I'm B";
}

string B::getBString()
{
    return bString;
}

ConcreteContextObject::ConcreteContextObject()
{
    description = "Simple Context Object";
}

ConcreteContextObject::~ConcreteContextObject()
{
}

A* ConcreteContextObject::getA()
{
    return a;
}

B* ConcreteContextObject::getB()
{
    return b;
}

void ConcreteContextObject::setA(A* aVar)
{
    a = aVar;
}

void ConcreteContextObject::setB(B* bVar)
{
    b = bVar;
}

void ConcreteContextObject::setDescription(const string& desc)
{
    if(desc.size() == 0)
        return;
    description = desc;
    DATA_INFO_VAL("Description Set at", description);
}

const string& ConcreteContextObject::getDescription() const
{
    return description;
}

} /* DATA */
} /* TESTBENCH */
} /* IT */
