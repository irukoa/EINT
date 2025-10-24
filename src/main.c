#include "CLI_Processing.h"
#include "CSV_Processing.h"
#include "EINT.h"
#include "Prime_Factors.h"

#ifndef BUFFER_MIN_SIZE
#define BUFFER_MIN_SIZE (size_t)1024
#endif

int main(int   argc,
         char *argv[]) {

  // Step 1: Process CLI input.

  bool redirected_stdin = (ftell(stdin) >= 0);

  unsigned int base = 2;

  bool v_flag = false;

  bool   cust_bufsize = false;
  size_t bufsize      = BUFFER_MIN_SIZE;

  bool  file_flag = false;
  char *file      = NULL;

  bool process_cols = true;

#ifdef DBG_PRF
  int CLIstatus;
  int CSVstatus;
#endif

#ifdef DBG_PRF
  CLIstatus =
#endif
      check_command_line_input(argc, argv, &v_flag, &base, &file_flag, &file,
                               &process_cols, &cust_bufsize, &bufsize,
                               BUFFER_MIN_SIZE);

#ifdef DBG_PRF
  fprintf(stderr, "========== DEBUG INFO ==========\n");
  fprintf(stderr, "STDIN OPEN: %i\n", redirected_stdin);
  fprintf(stderr, "BASE: %u\n", base);
  fprintf(stderr, "V FLAG: %i\n", v_flag);
  fprintf(stderr, "C FLAG: %i\n", cust_bufsize);
  fprintf(stderr, "bufsize: %u\n", (unsigned int)bufsize);
  fprintf(stderr, "F FLAG: %i\n", file_flag);
  fprintf(stderr, "FILE: \"%s\"\n", file);
  if (process_cols) {
    fprintf(stderr, "INTEGRATE ALONG COLS.\n");
  } else {
    fprintf(stderr, "INTEGRATE ALONG ROWS.\n");
  }
  fprintf(stderr, "========== ========== ==========\n");
#endif

#ifdef DBG_PRF
  if (CLIstatus == EXIT_FAILURE) {
    fprintf(stderr, "Error during CLI processing.\n");
    exit(EXIT_FAILURE);
  }
#endif

  if (v_flag)
    print_version(argv);

  if (BUFFER_MIN_SIZE > bufsize) {
    fprintf(stderr, "Minimum buffer column size is %u.\n",
            (unsigned int)BUFFER_MIN_SIZE);
    exit(EXIT_FAILURE);
  }

  if (file_flag && redirected_stdin) {
    fprintf(stderr, "File and redirected input set.\n");
    exit(EXIT_FAILURE);
  }

  // Step 2: read and check data input.

  size_t csv_ncols   = 0;
  size_t csv_nrows   = 0;
  FILE  *file_stream = NULL;

  double **CSV = NULL;

  if (file_flag) {
    if (v_flag) {
      fprintf(stdout, "Processing file %s\n", file);
    }
    file_stream = fopen(file, "r");
    if (file_stream == NULL) {
      fprintf(stderr, "%s : %s\n", file, strerror(errno));
      free(file);
      exit(EXIT_FAILURE);
    }
#ifdef DBG_PRF
    CSVstatus =
#endif
        read_csv(file_stream, bufsize, &CSV, &csv_ncols, &csv_nrows);
#ifdef DBG_PRF
    if (CSVstatus == EXIT_FAILURE) {
      fprintf(stderr, "Error during CSV processing.\n");
      exit(EXIT_FAILURE);
    }
#endif
    fclose(file_stream);
    free(file);
  } else {
    if (v_flag) {
      fprintf(stdout, "Processing standard input.\n");
    }
#ifdef DBG_PRF
    CSVstatus =
#endif
        read_csv(stdin, bufsize, &CSV, &csv_ncols, &csv_nrows);
#ifdef DBG_PRF
    if (CSVstatus == EXIT_FAILURE) {
      fprintf(stderr, "Error during CSV processing.\n");
      exit(EXIT_FAILURE);
    }
#endif
  }

#ifdef DBG_PRF
  fprintf(stderr, "========== ========== ==========\n");
  fprintf(stderr, "ROWS in CSV : %u\n", (unsigned int)csv_nrows);
  fprintf(stderr, "COLS in CSV : %u\n", (unsigned int)csv_ncols);
  fprintf(stderr, "========== ========== ==========\n");
  fprintf(stderr, "Printing CSV file.\n");
  for (size_t i = 0; i < csv_nrows; i++) {
    for (size_t j = 0; j < csv_ncols; j++) {
      fprintf(stderr, "%.10e ", CSV[i][j]);
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "========== ========== ==========\n");
#endif

  if (v_flag) {
    fprintf(stdout, "Sucessfully processed input stream.\n");
  }

  // Step 3: computation.

  size_t datasize   = 0;
  size_t resultsize = 0;

  if (process_cols) {
    datasize   = csv_nrows;
    resultsize = csv_ncols;
  } else {
    datasize   = csv_ncols;
    resultsize = csv_nrows;
  }

  if (datasize <= 1) {
    fprintf(stderr, "Error: data size is smaller or equal to 1\n");
    exit(EXIT_FAILURE);
  }

  double *data = (double *)malloc(datasize * sizeof(double));
  if (data == NULL) {
    fprintf(stderr, "Error allocating data : size: %u : %s\n",
            (unsigned int)datasize, strerror(errno));
    exit(EXIT_FAILURE);
  }
  double *result = (double *)malloc(resultsize * sizeof(double));
  if (result == NULL) {
    fprintf(stderr, "Error allocating result : size: %u : %s\n",
            (unsigned int)resultsize, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (process_cols) {
    for (size_t i = 0; i < csv_ncols; i++) {
      if (v_flag) {
        fprintf(stdout, "Processing column %u / %u.\n", (unsigned int)(i + 1),
                (unsigned int)csv_ncols);
      }
      for (size_t j = 0; j < csv_nrows; j++) {
        data[j] = CSV[j][i];
      }
      result[i] = extrapolation_double(data, csv_nrows, (int)base);
    }
  } else {
    for (size_t i = 0; i < csv_nrows; i++) {
      if (v_flag) {
        fprintf(stdout, "Processing row %u / %u.\n", (unsigned int)(i + 1),
                (unsigned int)csv_nrows);
      }
      for (size_t j = 0; j < csv_ncols; j++) {
        data[j] = CSV[i][j];
      }
      result[i] = extrapolation_double(data, csv_ncols, (int)base);
    }
  }

  // Step 4: return results.

  if (v_flag) {
    unsigned int power =
        (unsigned int)get_factor_power((int)datasize - 1, (int)base);
    fprintf(stdout, "Base is %u, data size is %u.\n", base,
            (unsigned int)datasize);
    fprintf(stdout, "A factor of (%u - 1) is %u^%u.\n", (unsigned int)datasize,
            base, power);
    fprintf(stdout, "Expected accuracy is O(h^2*%u).\n", power);
    fprintf(stdout, "Results:\n");
  }

  if (process_cols) {
    for (size_t i = 0; i < csv_ncols; i++) {
      fprintf(stdout, "%.10e ", result[i]);
    }
    fprintf(stdout, "\n");
  } else {
    for (size_t i = 0; i < csv_nrows; i++) {
      fprintf(stdout, "%.10e\n", result[i]);
    }
  }

  // Step 5: memory cleanup and finish.

  for (size_t i = 0; i < csv_nrows; i++) {
    free(CSV[i]);
  }

  if (csv_nrows > 0) {
    free(CSV);
  }
  free(data);
  free(result);

  exit(EXIT_SUCCESS);
}
