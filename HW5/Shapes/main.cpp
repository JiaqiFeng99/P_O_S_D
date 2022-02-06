#include "cppunitlite\TestHarness.h"
#include "ut.h"

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}
