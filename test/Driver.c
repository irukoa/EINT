// Common headers.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the test suites.
#include "Test_CLI_Processing.c"
#include "user.c"

int main() {
  fprintf(stderr, "\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, ">>Starting TESTS\n");
  fprintf(stderr, ">>Test suite #1: CLI Processing\n");
  fprintf(stderr, ">>Test 1.1: print help\n");
  CLI_Processing_Test_print_help();
  fprintf(stderr, ">>Test 1.2: print version\n");
  CLI_Processing_Test_print_version();
  fprintf(stderr, ">>Test 1.3: check CLI processing\n");
  CLI_Processing_Test_check_command_line_input();
  usertest();
  fprintf(stderr, ">>TESTS Finished\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, "\n");
  return 0;
}
