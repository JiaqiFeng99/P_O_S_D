#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "Analyzer.h"
#include <string>
#include <iostream>
#include <cstdio>
int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}

