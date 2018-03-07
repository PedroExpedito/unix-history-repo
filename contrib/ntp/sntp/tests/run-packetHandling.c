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
#include "ntp_debug.h"
#include "ntp_stdlib.h"
#include "ntp_types.h"
#include "sntptest.h"
#include "kod_management.h"
#include "main.h"
#include "networking.h"
#include "ntp.h"

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_GenerateUnauthenticatedPacket(void);
extern void test_GenerateAuthenticatedPacket(void);
extern void test_OffsetCalculationPositiveOffset(void);
extern void test_OffsetCalculationNegativeOffset(void);
extern void test_HandleUnusableServer(void);
extern void test_HandleUnusablePacket(void);
extern void test_HandleServerAuthenticationFailure(void);
extern void test_HandleKodDemobilize(void);
extern void test_HandleKodRate(void);
extern void test_HandleCorrectPacket(void);


//=======Suite Setup=====
static void suite_setup(void)
{
extern int change_logfile(const char*, int);
change_logfile("stderr", 0);
}

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
  suite_setup();
  UnityBegin("packetHandling.c");
  RUN_TEST(test_GenerateUnauthenticatedPacket, 17);
  RUN_TEST(test_GenerateAuthenticatedPacket, 18);
  RUN_TEST(test_OffsetCalculationPositiveOffset, 19);
  RUN_TEST(test_OffsetCalculationNegativeOffset, 20);
  RUN_TEST(test_HandleUnusableServer, 21);
  RUN_TEST(test_HandleUnusablePacket, 22);
  RUN_TEST(test_HandleServerAuthenticationFailure, 23);
  RUN_TEST(test_HandleKodDemobilize, 24);
  RUN_TEST(test_HandleKodRate, 25);
  RUN_TEST(test_HandleCorrectPacket, 26);

  return (UnityEnd());
}
