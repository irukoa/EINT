#include "CLI_Processing.h"

void CLI_Processing_Test_print_help() {
  char *argv = "Teint";
  print_help(&argv, 10);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_print_version() {
  char *argv = "Teint";
  print_version(&argv);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_h() {

  char *args[] = {"Teint", "-h", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_SUCCESS);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_cvalid() {

  char *args[] = {"Teint", "-c11", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_SUCCESS);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_cinvalid() {

  char *args[] = {"Teint", "-c -219348239", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_FAILURE);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_bvalid() {

  char *args[] = {"Teint", "-b11", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_SUCCESS);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_binvalid() {

  char *args[] = {"Teint", "-b9", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_FAILURE);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_fvalid() {

  char *args[] = {"Teint", "-f a.dat", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_SUCCESS);
  fprintf(stderr, ">>Test OK\n");
}

void CLI_Processing_Test_check_command_line_input_invalid_flag() {

  char *args[] = {"Teint", "-d", NULL};
  int   argc   = 2;

  size_t buf_min_size = 10;

  bool         v_flag;
  unsigned int base;
  bool         file_flag;
  char        *file;
  bool         process_cols;
  bool         cust_bufsize;
  size_t       bufsize;

  int status = check_command_line_input(argc, args, &v_flag, &base, &file_flag,
                                        &file, &process_cols, &cust_bufsize,
                                        &bufsize, buf_min_size);

  assert(status == EXIT_FAILURE);
  fprintf(stderr, ">>Test OK\n");
}
