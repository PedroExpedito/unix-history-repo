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
#include "ntp_stdlib.h"
#include "sockaddrtest.h"

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_IPv4AddressOnly(void);
extern void test_IPv4AddressWithPort(void);
extern void test_IPv6AddressOnly(void);
extern void test_IPv6AddressWithPort(void);
extern void test_IllegalAddress(void);
extern void test_IllegalCharInPort(void);


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
  UnityBegin("decodenetnum.c");
  RUN_TEST(test_IPv4AddressOnly, 7);
  RUN_TEST(test_IPv4AddressWithPort, 8);
  RUN_TEST(test_IPv6AddressOnly, 10);
  RUN_TEST(test_IPv6AddressWithPort, 11);
  RUN_TEST(test_IllegalAddress, 13);
  RUN_TEST(test_IllegalCharInPort, 14);

  return (UnityEnd());
}
