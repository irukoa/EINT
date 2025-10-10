#include "CSV_Processing.h"

void read_csv(FILE     *stream,
              size_t    max_colsize,
              size_t    max_rowsize,
              double ***CSV,
              size_t   *ncols,
              size_t   *nrows) {

  /* When processing CSV files, we follow
     https://www.rfc-editor.org/rfc/rfc4180.txt with:
     - No irregular data:
     - - Row#1, with C columns acts as reference for the rest of the CSV.
     - - For Row#i with C_i columns:
     - - - C_i >= C: Only the first C columns are considered.
     - - - C_i < C: Error.
     - CSV headers are NOT allowed.
     For manual input, press ENTER with no data to end the stream.
  */

  size_t counter = 0;
  size_t in_len  = 0;

  char       copy_buffer[max_rowsize];
  char      *token        = NULL;
  char      *check        = NULL;
  const char separators[] = " ,;";

  char local_buffer[max_rowsize][max_colsize];

  while (fgets(local_buffer[counter], max_colsize, stream) != NULL) {
    in_len = strlen(local_buffer[counter]);
    if (in_len == 1 && local_buffer[counter][in_len - 1] == '\n') {
      goto read_end;
    }
    counter++;
  }

  if (!feof(stdin)) {
    fprintf(stderr, "Error reading data : could not read whole CSV file.\n");
    exit(EXIT_FAILURE);
  }

read_end:

  *nrows = counter;

  strcpy(copy_buffer, local_buffer[0]);
  token   = strtok(copy_buffer, separators);
  counter = 0;
  while (token != NULL) {
    counter++;
    token = strtok(NULL, separators);
  }

  *ncols = counter;

  *CSV = (double **)malloc((*nrows) * sizeof(double *));
  if (*CSV == NULL) {
    fprintf(stderr, "Error allocating CSV : nrows: %li : %s\n", *nrows,
            strerror(errno));
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < *nrows; i++) {
    (*CSV)[i] = (double *)malloc((*ncols) * sizeof(double));
    if ((*CSV)[i] == NULL) {
      fprintf(stderr, "Error allocating CSV : ncols: %li : %s\n", *ncols,
              strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < *nrows; i++) {
    token = strtok(local_buffer[i], separators);
    for (size_t j = 0; j < *ncols; j++) {
      if (token == NULL) {
        fprintf(stderr, "Error reading data : CSV file is irregular.\n");
        exit(EXIT_FAILURE);
      }
      ((*CSV)[i])[j] = strtod(token, &check);
      if (!(strlen(check) == 0 || token[strlen(token) - 1] == '\n')) {
        fprintf(stderr, "CSV input value not recognized:\n");
        fprintf(stderr, "Row : %li | Col : %li\n", i + 1, j + 1);
        fprintf(stderr, "Value : %s\n", token);
        exit(EXIT_FAILURE);
      }
      token = strtok(NULL, separators);
    }
  }
}
