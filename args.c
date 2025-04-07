#include "args.h"
#include <argp.h>
#include <stdlib.h>

const char *argp_program_version = "0.0.1";
const char *argp_program_bug_address = "nicolas.lisgaras@gmail.com";
static char doc[] = "Simple lightweight TCP/IP webserver";
static char args_doc[] = "";
static struct argp_option options[] = {
    {"reuseaddr", OPT_REUSEADDR, 0, 0,
     "Add 'reuse address' option to TCP socket"},
    {"port", 'p', "port", 0, "Specify port (default: 8000)"},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;
  switch (key) {
  case OPT_REUSEADDR:
    arguments->useReuseAddr = true;
    break;
  case 'p':
    printf("%p\n", arg);
    arguments->port = arg ? atoi(arg) : DEFAULT_PORT;
    break;
  case ARGP_KEY_ARG:
    return 0;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

static struct arguments args = {0};

void parse_args(int argc, char **argv) {

  args.mode = DEVMODE;
  args.useReuseAddr = false;
  args.port = DEFAULT_PORT;

  argp_parse(&argp, argc, argv, 0, 0, &args);
}

struct arguments get_args(void) { return args; }
