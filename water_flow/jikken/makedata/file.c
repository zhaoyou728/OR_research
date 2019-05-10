#include <stdio.h>
#include "file.h"

FILE* FILEOPEN(char* fpath, char* mode)
{
  FILE* fp = NULL;

  if( (fp = fopen(fpath, mode)) == NULL ){
    fprintf(stderr, "Error: Can't open %s.\n", fpath);
    exit(1);
    // or return NULL;
  }

  return fp;
}
