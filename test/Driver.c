// Common headers.
#include <stdio.h>
#include <stdlib.h>

// Include the test suites.
#include "a.c"
#include "user.c"

int main() {
  fprintf(stderr, "\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, ">>Starting TESTS\n");
  a_test();
  usertest();
  fprintf(stderr, ">>TESTS Finished\n");
  fprintf(stderr, "===============================\n");
  fprintf(stderr, "\n");
  return 0;
}
