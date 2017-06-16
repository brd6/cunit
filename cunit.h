#ifndef CUNIT_H_
# define CUNIT_H_

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# define COLOR_RED	"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE	"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN	"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"

# define PRINT_ERRNO() (errno != 0 ? strerror(errno) : 0)

# ifndef DEBUG
#  define PRINT_DEBUG(format, ...)
#  define PRINT_WARNING(format, ...)
#  define PRINT_ERROR(format, ...)
# else
#  define PRINT_DEBUG(format, ...) dprintf(2, "[DEBUG]" format "\n",	\
					   ##__VA_ARGS__)
#  define PRINT_WARNING(format, ...) dprintf(2, COLOR_YELLOW "[WARN]"	\
					     COLOR_RESET		\
					     " %s:%d: errno: %s - "format"\n", \
					     __FILE__, __LINE__, \
					     PRINT_ERRNO(),	 \
					     ##__VA_ARGS__)
#  define PRINT_ERROR(format, ...) dprintf(2, COLOR_RED "[ERROR]"	\
					   COLOR_RESET			\
					   " %s:%d: errno: %s - "format"\n", \
					   __FILE__, __LINE__, PRINT_ERRNO(), \
					   ##__VA_ARGS__)
# endif

extern int _tests_run_;
extern int _tests_passed_;
extern int _ret_;

# define CU_INIT() int _tests_run_ = 0; int _tests_passed_ = 0; int _ret_ = 0;

# define TEST(_name) static int _name()

# define CU_ASSERT(test) _ret_ = test;
# define CU_ASSERT_MSG(test, message, ...) if (!(test)) { PRINT_ERROR(message, ## __VA_ARGS__); } _ret_ = test;
# define CU_ASSERT_NUM(nb1, nb2, op, message, ...) CU_ASSERT_MSG(nb1 op nb2, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_EQ(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, ==, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_NE(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, !=, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_LT(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, <, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_LE(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, <=, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_GT(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, >, message, ## __VA_ARGS__)
# define CU_ASSERT_NUM_GE(nb1, nb2, message, ...) CU_ASSERT_NUM(nb1, nb2, >=, message, ## __VA_ARGS__)
# define CU_ASSERT_STR(s1, s2, op, message, ...) CU_ASSERT_MSG(strcmp(s1 == NULL ? "" : s1, s2 == NULL ? "" : s2) op 0, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_EQ(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, ==, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_NE(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, !=, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_LT(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, <, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_LE(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, <=, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_GT(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, >, message, ## __VA_ARGS__)
# define CU_ASSERT_STR_GE(str1, str2, message, ...) CU_ASSERT_STR(str1, str2, >=, message, ## __VA_ARGS__)
# define CU_ASSERT_PTR(ptr1, ptr2, op, message, ...) CU_ASSERT_MSG(ptr1 op ptr2, message, ## __VA_ARGS__)
# define CU_ASSERT_PTR_NULL(ptr, message, ...) CU_ASSERT_PTR(ptr, NULL, ==, message, ## __VA_ARGS__)
# define CU_ASSERT_PTR_NON_NULL(ptr, message, ...) CU_ASSERT_PTR(ptr, NULL, !=, message, ## __VA_ARGS__)
# define CU_ASSERT_PTR_EQ(ptr1, ptr2, message, ...) CU_ASSERT_PTR(ptr1, ptr2, ==, message, ## __VA_ARGS__)
# define CU_ASSERT_PTR_NE(ptr1, ptr2, message, ...) CU_ASSERT_PTR(ptr1, ptr2, !=, message, ## __VA_ARGS__)
# define CU_RUN_TEST(test) printf("[ RUN      ] %d - %s\n", _tests_run_, "" #test); \
  test();								\
  _tests_run_++;								\
  if (!_ret_) { printf("[  %sFAILED%s  ] %d - %s\n", COLOR_RED, COLOR_RESET, _tests_run_ - 1, "" #test); return ; } \
  else { printf("[       %sOK%s ] %d - %s\n", COLOR_GREEN, COLOR_RESET, _tests_run_ - 1, "" #test); _tests_passed_++; }
# define RUN_ALL_TESTS(name) int main(int ac, char **av) {		\
    printf("Running %s from %s\n", "" #name, av[0]);			\
    printf("[----------] cunit setup\n");				\
    name();								\
    printf("[----------] cunit end\n");					\
    if (_tests_passed_ != _tests_run_) {					\
      printf("\n1 %sFAILED TEST%s\n", COLOR_RED, COLOR_RESET);					\
    }									\
    else {								\
      printf("\n%sALL TESTS PASSED%s\n", COLOR_GREEN, COLOR_RESET);					\
    }									\
    printf("Tests run: %d\n", _tests_run_);				\
    exit(_tests_passed_ != _tests_run_);					\
  }

#endif /* !CUNIT_H_ */
