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
#include "ntp_types.h"
#include "sntptest.h"
#include "crypto.h"

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_MakeMd5Mac(void);
extern void test_MakeSHA1Mac(void);
extern void test_VerifyCorrectMD5(void);
extern void test_VerifySHA1(void);
extern void test_VerifyFailure(void);
extern void test_PacketSizeNotMultipleOfFourBytes(void);


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
  UnityBegin("crypto.c");
  RUN_TEST(test_MakeMd5Mac, 12);
  RUN_TEST(test_MakeSHA1Mac, 13);
  RUN_TEST(test_VerifyCorrectMD5, 14);
  RUN_TEST(test_VerifySHA1, 15);
  RUN_TEST(test_VerifyFailure, 16);
  RUN_TEST(test_PacketSizeNotMultipleOfFourBytes, 17);

  return (UnityEnd());
}
