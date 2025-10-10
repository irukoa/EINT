#ifndef CSV_PROCESDING
#define CSV_PROCESDING

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_csv(FILE     *stream,
              size_t    max_colsize,
              size_t    max_rowsize,
              double ***CSV,
              size_t   *ncols,
              size_t   *nrows);

#endif
