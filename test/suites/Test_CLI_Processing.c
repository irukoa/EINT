#include "CLI_Processing.h"

void CLI_Processing_Test_print_help() {
  char *argv = "Teint";
  print_help(&argv, 10, 10);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_print_version() {
  char *argv = "Teint";
  print_version(&argv);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input() {

  int argc = 2;

  char *argv0 = "Teint";
  char *argv1 = "-h";

  char **argv = (char **)malloc((argc + 1) * sizeof(char *));
  assert(argv != NULL);
  argv[0] = (char *)malloc(strlen(argv0 + 1) * sizeof(char));
  assert(argv[0] != NULL);
  strcpy(argv[0], argv0);
  argv[1] = (char *)malloc(strlen(argv1 + 1) * sizeof(char));
  assert(argv[1] != NULL);
  strcpy(argv[1], argv1);
  argv[argc] = NULL;

  size_t buf_min_colsize = 10;
  size_t buf_min_rowsize = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_buf_colsize;
  size_t       buf_colsize;
  bool         cust_buf_rowsize;
  size_t       buf_rowsize;

  int status = check_command_line_input(
      argc, argv, &v_flag, &base, &file_flag, &file, &process_cols,
      &cust_buf_colsize, &buf_colsize, buf_min_colsize, &cust_buf_rowsize,
      &buf_rowsize, buf_min_rowsize);

  free(argv[0]);
  free(argv[1]);
  free(argv[argc]);
  free(argv);

  assert(status == EXIT_SUCCESS);
  fprintf(stderr, ">>Test OK\n");
}
