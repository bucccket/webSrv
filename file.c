#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int openFile(const char *filename, struct File *file) {
  char errmsg[strlen(filename) + 11]; // filename len + extra text
  sprintf(errmsg, "File %s Open", filename);

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    perror(errmsg);
    return FILE_NOT_FOUND;
  }

  fseek(fp, 0L, SEEK_END);
  file->size = ftell(fp);
  rewind(fp);

  file->data = calloc(file->size, sizeof(char));
  fread(file->data, file->size, sizeof(char), fp);

  fclose(fp);

  return FILE_OK;
}

int closeFile(struct File *file) {

  if (file->data) {
    free(file->data);
    file->data = NULL;
  }
  *file = (struct File){0};

  return FILE_OK;
}
