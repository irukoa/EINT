// Common headers.
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the test suites.
#include "Test_CLI_Processing.c"
#include "Test_CSV_Processing.c"
#include "Test_EINT.c"

int main() {
  fprintf(stderr, "\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, ">>Starting UNIT TESTS\n");
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
  fprintf(stderr, ">>Test suite #2: CSV Processing\n");
  fprintf(stderr, ">>Test 2.1: check CSV processing: valid file\n");
  CSV_Processing_Test_check_valid_file();
  fprintf(stderr, ">>Test 2.2: check CSV processing: irregular file\n");
  CSV_Processing_Test_check_irregular_file();
  fprintf(stderr, ">>Test 2.3: check CSV processing: faulty file\n");
  CSV_Processing_Test_check_faulty_conversion();
  fprintf(stderr, ">>Test suite #3: EINT\n");
  fprintf(stderr, ">>Test 3.1: check EINT: trivial case (sp)\n");
  EINT_Test_check_float_trivial_case();
  fprintf(stderr, ">>Test 3.2: check EINT: trivial case (dp)\n");
  EINT_Test_check_double_trivial_case();
  fprintf(
      stderr,
      ">>Test 3.3: check EINT: 1st order polynomial (sp) (No Extrapolation)\n");
  EINT_Test_check_float_1stOrdPoly_nE();
  fprintf(
      stderr,
      ">>Test 3.4: check EINT: 1st order polynomial (dp) (No Extrapolation)\n");
  EINT_Test_check_double_1stOrdPoly_nE();
  fprintf(
      stderr,
      ">>Test 3.5: check EINT: 1st order polynomial (sp) (Extrapolation)\n");
  EINT_Test_check_float_1stOrdPoly_E();
  fprintf(
      stderr,
      ">>Test 3.6: check EINT: 1st order polynomial (dp) (Extrapolation)\n");
  EINT_Test_check_double_1stOrdPoly_E();
  fprintf(
      stderr,
      ">>Test 3.7: check EINT: 4th order polynomial (sp) (No Extrapolation)\n");
  EINT_Test_check_float_4thOrdPoly_nE();
  fprintf(
      stderr,
      ">>Test 3.8: check EINT: 4th order polynomial (dp) (No Extrapolation)\n");
  EINT_Test_check_double_4thOrdPoly_nE();
  fprintf(
      stderr,
      ">>Test 3.9: check EINT: 4th order polynomial (sp) (Extrapolation)\n");
  EINT_Test_check_float_4thOrdPoly_E();
  fprintf(
      stderr,
      ">>Test 3.10: check EINT: 4th order polynomial (dp) (Extrapolation)\n");
  EINT_Test_check_double_4thOrdPoly_E();
  fprintf(stderr, ">>UNIT TESTS Finished\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, "\n");
  return 0;
}
