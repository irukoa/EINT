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
  fprintf(stderr, ">>Test 1.3: check CLI processing: -h option\n");
  CLI_Processing_Test_check_command_line_input_h();
  fprintf(stderr, ">>Test 1.4: check CLI processing: -c option valid input\n");
  CLI_Processing_Test_check_command_line_input_cvalid();
  fprintf(stderr,
          ">>Test 1.5: check CLI processing: -c option invalid input\n");
  CLI_Processing_Test_check_command_line_input_cinvalid();
  fprintf(stderr, ">>Test 1.6: check CLI processing: -r option valid input\n");
  CLI_Processing_Test_check_command_line_input_rvalid();
  fprintf(stderr,
          ">>Test 1.7: check CLI processing: -r option invalid input\n");
  CLI_Processing_Test_check_command_line_input_rinvalid();
  fprintf(stderr, ">>Test 1.8: check CLI processing: -b option valid input\n");
  CLI_Processing_Test_check_command_line_input_bvalid();
  fprintf(stderr,
          ">>Test 1.9: check CLI processing: -b option invalid input\n");
  CLI_Processing_Test_check_command_line_input_binvalid();
  fprintf(stderr, ">>Test 1.10: check CLI processing: -f option valid input\n");
  CLI_Processing_Test_check_command_line_input_fvalid();
  fprintf(stderr, ">>Test 1.10: check CLI processing: invalid flag\n");
  CLI_Processing_Test_check_command_line_input_invalid_flag();
  usertest();
  fprintf(stderr, ">>TESTS Finished\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, "\n");
  return 0;
}
