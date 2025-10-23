#include "CSV_Processing.h"

#ifdef DBG_PRF
int
#else
void
#endif
read_csv(FILE     *stream,
              size_t    max_bufsize,
              double ***CSV,
              size_t   *ncols,
              size_t   *nrows) {

  /* When processing CSV files, we follow
     https://www.rfc-editor.org/rfc/rfc4180.txt with:
     - No irregular data:
     - - Row#1, with C columns acts as reference for the rest of the CSV.
     - - For Row#i with C_i columns:
     - - - C_i > C: Error.
     - - - C_i < C: Error.
     - CSV headers are NOT allowed.
     For manual input, press ENTER with no data to end the stream.
  */

  size_t      counter     = 0;
  size_t      in_len      = 0;
  StringNode *string_list = NULL;

  char *token     = NULL;
  char *check     = NULL;
  char *numString = NULL;

  const char separators[] = " ,;";

  char  local_buffer[max_bufsize];
  char *copy_buffer = NULL;

#ifdef DBG_PRF
  int status;
#endif

  while (fgets(local_buffer, max_bufsize, stream) != NULL) {
    in_len = strlen(local_buffer);
    if (in_len == 1 && local_buffer[in_len - 1] == '\n') {
      goto read_end;
    }
    addNodeAtEnd(&string_list, local_buffer);
    counter++;
  }

  if (!feof(stream)) {
    fprintf(stderr, "Error reading data : could not read whole CSV file.\n");
    freeList(&string_list);
#ifdef DBG_PRF
    status = EXIT_FAILURE;
    return (status);
#else
    exit(EXIT_FAILURE);
#endif
  }

read_end:

  *nrows = counter;

  if (*nrows == 0) {
    freeList(&string_list);
#ifdef DBG_PRF
    status = EXIT_SUCCESS;
    return (status);
#else
    return;
#endif
  }

  copy_buffer = sourceString(string_list);
  token       = strtok(copy_buffer, separators);
  counter     = 0;
  while (token != NULL) {
    counter++;
    token = strtok(NULL, separators);
  }
  free(copy_buffer);

  *ncols = counter;

  *CSV = (double **)malloc((*nrows) * sizeof(double *));
  if (*CSV == NULL) {
    fprintf(stderr, "Error allocating CSV : nrows: %li : %s\n", *nrows,
            strerror(errno));
    freeList(&string_list);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < *nrows; i++) {
    (*CSV)[i] = (double *)malloc((*ncols) * sizeof(double));
    if ((*CSV)[i] == NULL) {
      fprintf(stderr, "Error allocating CSV : ncols: %li : %s\n", *ncols,
              strerror(errno));
      freeList(&string_list);
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < *nrows; i++) {
    copy_buffer = sourceString(string_list);
    rmNodeAtBeggining(&string_list);
    token = strtok(copy_buffer, separators);
    for (size_t j = 0; j < *ncols; j++) {
      if (((token[strlen(token) - 1] == '\n') && (j != *ncols - 1)) ||
          ((token[strlen(token) - 1] != '\n') && (j == *ncols - 1))) {
        fprintf(stderr, "Error reading data : CSV file is irregular.\n");
        free(copy_buffer);
        freeList(&string_list);
#ifdef DBG_PRF
        status = EXIT_FAILURE;
        return (status);
#else
        exit(EXIT_FAILURE);
#endif
      }
      numString = strdup(token);
      if (j == *ncols - 1) {
        // We remove the \n character from numString.
        numString[strlen(numString) - 1] = '\0';
      }
      ((*CSV)[i])[j] = strtod(numString, &check);
      if (strlen(check) != 0) {
        fprintf(stderr, "CSV input value not recognized:\n");
        fprintf(stderr, "Row : %li | Col : %li\n", i + 1, j + 1);
        fprintf(stderr, "Value : %s\n", token);
        free(numString);
        free(copy_buffer);
        freeList(&string_list);
#ifdef DBG_PRF
        status = EXIT_FAILURE;
        return (status);
#else
        exit(EXIT_FAILURE);
#endif
      }
      free(numString);
      token = strtok(NULL, separators);
    }
    free(copy_buffer);
  }
  freeList(&string_list);
#ifdef DBG_PRF
  status = EXIT_SUCCESS;
  return (status);
#endif
}
