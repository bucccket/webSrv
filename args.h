#pragma once

#include <argp.h>
#include <stdbool.h>

// Keys for options without short-opts
#define OPT_REUSEADDR 1

#define DEFAULT_PORT 8000

void parse_args(int argc, char **argv);

struct arguments get_args(void);

struct arguments {
  enum { DEVMODE } mode;
  bool useReuseAddr;
  int port;
};
