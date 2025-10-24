#include "CSV_Processing.h"

void CSV_Processing_Test_check_valid_file() {

  static double tol = 10.0 * DBL_EPSILON;

  FILE *file_stream = fopen("./test/suites/ValidCSV.dat", "r");

  double **CSV       = NULL;
  size_t   csv_ncols = 0;
  size_t   csv_nrows = 0;

  size_t bufsize = 1024;

  if (file_stream == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int status = read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
  fclose(file_stream);

  assert(status == EXIT_SUCCESS);
  assert(CSV != NULL);
  assert(csv_ncols == 10);
  assert(csv_nrows == 9);
  assert(fabs(CSV[0][0] - (double)1) <= tol);
  for (size_t i = 0; i < csv_nrows; i++) {
    free(CSV[i]);
  }
  free(CSV);
  fprintf(stderr, ">>Test OK\n");
}

void CSV_Processing_Test_check_irregular_file() {

  static double tol = 10.0 * DBL_EPSILON;

  FILE *file_stream = NULL;
  int   status      = 0;

  double **CSV       = NULL;
  size_t   csv_ncols = 0;
  size_t   csv_nrows = 0;

  size_t bufsize = 1024;

  file_stream = fopen("./test/suites/IrregularCSV1.dat", "r");

  if (file_stream == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  status = read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
  fclose(file_stream);

  assert(status == EXIT_FAILURE);
  assert(CSV != NULL);
  assert(csv_ncols == 10);
  assert(csv_nrows == 9);
  assert(fabs(CSV[0][0] - (double)1) <= tol);
  for (size_t i = 0; i < csv_nrows; i++) {
    free(CSV[i]);
  }
  free(CSV);

  file_stream = fopen("./test/suites/IrregularCSV2.dat", "r");

  if (file_stream == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  status = read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
  fclose(file_stream);

  assert(status == EXIT_FAILURE);
  assert(CSV != NULL);
  assert(csv_ncols == 10);
  assert(csv_nrows == 9);
  assert(fabs(CSV[0][0] - (double)1) <= tol);
  for (size_t i = 0; i < csv_nrows; i++) {
    free(CSV[i]);
  }
  free(CSV);
  fprintf(stderr, ">>Test OK\n");
}

void CSV_Processing_Test_check_faulty_conversion() {

  FILE *file_stream = fopen("./test/suites/FaultyCSV.dat", "r");

  double **CSV       = NULL;
  size_t   csv_ncols = 0;
  size_t   csv_nrows = 0;

  size_t bufsize = 1024;

  if (file_stream == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int status = read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
  fclose(file_stream);

  assert(status == EXIT_FAILURE);
  assert(CSV != NULL);
  assert(csv_ncols == 10);
  assert(csv_nrows == 9);
  for (size_t i = 0; i < csv_nrows; i++) {
    free(CSV[i]);
  }
  free(CSV);
  fprintf(stderr, ">>Test OK\n");
}

void CSV_Processing_Test_check_empty() {

  FILE *file_stream = fopen("./test/suites/EmptyCSV.dat", "r");

  double **CSV       = NULL;
  size_t   csv_ncols = 0;
  size_t   csv_nrows = 0;

  size_t bufsize = 1024;

  if (file_stream == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int status = read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
  fclose(file_stream);

  assert(status == EXIT_SUCCESS);
  assert(CSV == NULL);
  assert(csv_ncols == 0);
  assert(csv_nrows == 0);
  fprintf(stderr, ">>Test OK\n");
}
