/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>
#include "config.h"
#include "sntptest.h"
#include "fileHandlingTest.h"
#include "main.h"
#include "utilities.h"
#include <math.h>

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_IPv4Address(void);
extern void test_IPv6Address(void);
extern void test_SetLiVnMode1(void);
extern void test_SetLiVnMode2(void);
extern void test_PktOutput(void);
extern void test_LfpOutputBinaryFormat(void);
extern void test_LfpOutputDecimalFormat(void);


//=======Test Reset Option=====
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}

char const *progname;


//=======MAIN=====
int main(int argc, char *argv[])
{
  progname = argv[0];
  UnityBegin("utilities.c");
  RUN_TEST(test_IPv4Address, 16);
  RUN_TEST(test_IPv6Address, 17);
  RUN_TEST(test_SetLiVnMode1, 18);
  RUN_TEST(test_SetLiVnMode2, 19);
  RUN_TEST(test_PktOutput, 20);
  RUN_TEST(test_LfpOutputBinaryFormat, 21);
  RUN_TEST(test_LfpOutputDecimalFormat, 22);

  return (UnityEnd());
}
