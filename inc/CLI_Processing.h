#ifndef CLI_PROCESSING
#define CLI_PROCESSING

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_help(char  *argv[],
                size_t buf_min_colsize,
                size_t buf_min_rowsize);

void print_version(char *argv[]);

#ifdef DBG_PRF
int
#else
void
#endif
check_command_line_input(int           argc,
                              char         *argv[],
                              bool         *v_flag,
                              unsigned int *base,
                              bool         *file_flag,
                              char         *file[],
                              bool         *process_cols,
                              bool         *cust_buf_colsize,
                              size_t       *buf_colsize,
                              size_t        buf_min_colsize,
                              bool         *cust_buf_rowsize,
                              size_t       *buf_rowsize,
                              size_t        buf_min_rowsize);

#endif
