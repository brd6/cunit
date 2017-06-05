#include "cunit.h"

CU_INIT();

TEST(hello_world_test)
{
  CU_ASSERT_STR_EQ("hello world", "hello world", "Not match, must be 'hello world'");
  CU_ASSERT_STR_NE("hello world", "hello", "Not match, must be 'hello'");
}

TEST(number_42_test)
{
  CU_ASSERT_NUM_EQ(42, 42, "Not match, must be '42'");
}

void all_tests()
{
  CU_RUN_TEST(hello_world_test);
  CU_RUN_TEST(number_42_test);
}

RUN_ALL_TESTS(all_tests);
