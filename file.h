#pragma once
#include <stdio.h>
#include <stdlib.h>

#define FILE_OK 0
#define FILE_NOT_FOUND 1
#define FILE_OOM 2

struct File {
  size_t size;
  char *data;
};

int openFile(const char *filename, struct File *file);
int closeFile(struct File *file);
