#include "CLI_Processing.h"
#include "Prime_Factors.h"
#include "Project_Metadata.h"

void print_help(char  *argv[],
                size_t buf_min_colsize,
                size_t buf_min_rowsize) {
  fprintf(stdout,
          "Numerically integrate data employing the extrapolation method.\n");
  fprintf(stdout, "\n");
  fprintf(stdout,
          "Usage: %s [-v] [-h] [-b BASE] [-f FILE] [-t] "
          "[-c MAX_BUFFER_COL_SIZE] [-r MAX_BUFFER_ROW_SIZE]\n",
          argv[0]);
  fprintf(stdout, "\n");
  fprintf(stdout,
          "    -v,                    : print version and verbose option.\n");
  fprintf(stdout, "    -h,                    : print this help and exit.\n");
  fprintf(stdout, "    -b, BASE               : extrapolation base, a prime "
                  "number > 1. Default is 2.\n");
  fprintf(stdout, "                             Works best with the smallest "
                  "or most degenerate divisor of 'data_size-1'.\n");
  fprintf(stdout, "    -f, FILE               : process specified file.\n");
  fprintf(stdout, "    -t,                    : integrate row by row instead "
                  "of column by column.\n");
  fprintf(
      stdout,
      "    The next arguments are useful for processing large CSV files.\n");
  fprintf(stdout,
          "    -c, MAX_BUFFER_COL_SIZE: a custom maximum column size for "
          "reading CSV files. Must be > %li.\n",
          buf_min_colsize);
  fprintf(stdout,
          "    -r, MAX_BUFFER_ROW_SIZE: a custom maximum row size for reading "
          "CSV files. Must be > %li.\n",
          buf_min_rowsize);
  fprintf(stdout, "\n");
  fprintf(stdout, "When processing CSV files, we follow "
                  "https://www.rfc-editor.org/rfc/rfc4180.txt with:\n");
  fprintf(stdout, "- No irregular data:\n");
  fprintf(
      stdout,
      "- - Row#1, with C columns acts as reference for the rest of the CSV.\n");
  fprintf(stdout, "- - For Row#i with C_i columns:\n");
  fprintf(stdout, "- - - C_i >= C: Only the first C columns are considered.\n");
  fprintf(stdout, "- - - C_i  < C: Error.\n");
  fprintf(stdout, "- CSV headers are NOT allowed.\n");
  fprintf(stdout,
          "For manual input, press ENTER with no data to end the stream.\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "Full documentation: <%s>\n", REPO);
}

void print_version(char *argv[]) {
  fprintf(stdout, "%s version %s %s (EINT)\n", argv[0], VERSION, DATE);
}

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
                              size_t        buf_min_rowsize) {

  int          opt;
  char        *check = NULL;
  long int     tmp;
  extern char *optarg;
  extern int   optind, opterr, optopt;

  static char allowed_flags[] = "vhb:f:tc:r:";

  opterr = 0;
  optind = 1;

#ifdef DBG_PRF
  int status;
#endif

  while ((opt = getopt(argc, argv, allowed_flags)) != -1) {
    switch (opt) {
    case 'h':
      print_help(argv, buf_min_colsize, buf_min_rowsize);
#ifdef DBG_PRF
      status = EXIT_SUCCESS;
      return (status);
#else
      exit(EXIT_SUCCESS);
#endif
    case 'v':
      *v_flag = true;
      break;
    case 'c':
      *cust_buf_colsize = true;
      tmp               = strtol(optarg, &check, 10);
      if (*check != '\0' || tmp < 1) {
        fprintf(stderr, "-c option requires a positive integer value\n");
#ifdef DBG_PRF
        status = EXIT_FAILURE;
        return (status);
#else
        exit(EXIT_FAILURE);
#endif
      }
      *buf_colsize = (size_t)tmp;
      break;
    case 'r':
      *cust_buf_rowsize = true;
      tmp               = strtol(optarg, &check, 10);
      if (*check != '\0' || tmp < 1) {
        fprintf(stderr, "-r option requires a positive integer value\n");
#ifdef DBG_PRF
        status = EXIT_FAILURE;
        return (status);
#else
        exit(EXIT_FAILURE);
#endif
      }
      *buf_rowsize = (size_t)tmp;
      break;
    case 'f':
      *file_flag = true;
      *file      = strdup(optarg);
      if (*file == NULL) {
        fprintf(stderr, "Error obtaining target file : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
#ifdef DBG_PRF
      free(*file);
#endif
      break;
    case 't':
      *process_cols = false;
      break;
    case 'b':
      tmp = strtol(optarg, &check, 10);
      if (*check != '\0' || !(is_prime((int)tmp))) {
        fprintf(stderr, "-b option requires a prime number > 1\n");
#ifdef DBG_PRF
        status = EXIT_FAILURE;
        return (status);
#else
        exit(EXIT_FAILURE);
#endif
      }
      *base = tmp;
      break;
    default:
      fprintf(stderr, "Invalid option '-%c'\n", (char)optopt);
      fprintf(stdout,
              "Usage: %s [-v] [-h] [-b BASE] [-f FILE] [-t] "
              "[-c MAX_BUFFER_COL_SIZE] [-r MAX_BUFFER_ROW_SIZE]\n",
              argv[0]);
#ifdef DBG_PRF
      status = EXIT_FAILURE;
      return (status);
#else
      exit(EXIT_FAILURE);
#endif
    }
  }

  if (optind != argc) {
    fprintf(stderr, "Too many arguments\n");
#ifdef DBG_PRF
    status = EXIT_FAILURE;
    return (status);
#else
    exit(EXIT_FAILURE);
#endif
  }
#ifdef DBG_PRF
  status = EXIT_SUCCESS;
  return (status);
#endif
}
