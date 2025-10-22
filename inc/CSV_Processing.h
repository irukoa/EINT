#ifndef CSV_PROCESDING
#define CSV_PROCESDING

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "String_Linked_Lists.h"

#ifdef DBG_PRF
int
#else
void
#endif
read_csv(FILE     *stream,
              size_t    max_bufsize,
              double ***CSV,
              size_t   *ncols,
              size_t   *nrows);

#endif
