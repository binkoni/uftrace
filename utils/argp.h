#ifndef UFTRACE_ARGP
#define UFTRACE_ARGP

#include <errno.h>
#include <stdio.h>
#include <limits.h>

#define ARGP_ERR_UNKNOWN E2BIG
struct argp_state;
typedef error_t (*argp_parser_t)(int key, char *arg, struct argp_state *state);

enum argp_flags
{
	ARGP_PARSE_ARGV0,
	ARGP_NO_ERRS,
	ARGP_NO_ARGS,
	ARGP_IN_ORDER,
	ARGP_NO_HELP,
	ARGP_NO_EXIT,
	ARGP_LONG_ONLY,
	ARGP_SILENT
};

enum argp_keys
{
	ARGP_KEY_ARG = CHAR_MAX + 1,
	ARGP_KEY_ARGS,
	ARGP_KEY_END,
	ARGP_KEY_NO_ARGS,
	ARGP_KEY_INIT,
	ARGP_KEY_SUCCESS,
	ARGP_KEY_ERROR,
	ARGP_KEY_FINI
};

enum ARGP_HELP_FLAGS
{
	ARGP_HELP_USAGE,
	ARGP_HELP_SHORT_USAGE,
	ARGP_HELP_SEE,
	ARGP_HELP_LONG,
	ARGP_HELP_PRE_DOC,
	ARGP_HELP_POST_DOC,
	ARGP_HELP_DOC,
	ARGP_HELP_BUG_ADDR,
	ARGP_HELP_LONG_ONLY,
	ARGP_HELP_EXIT_ERR,
	ARGP_HELP_EXIT_OK,
	ARGP_HELP_STD_ERR,
	ARGP_HELP_STD_USAGE,
	ARGP_HELP_STD_HELP
};

struct argp {
	const struct argp_option *options;
	argp_parser_t parser;
	const char *args_doc;
	const char *doc;
	const struct argp_child *children;
	char *(*help_filter)(int key, const char *text, void *input);
	const char *argp_domain;
};

struct argp_state {
	const struct argp *const root_argp;
	int argc;
	char **argv;
	int next;
	unsigned flags;
	unsigned arg_num;
	int quoted;
	void *input;
	void **child_inputs;
	void *hook;
	char *name;
	FILE *err_stream;
	FILE *out_stream;
	void *pstate;
};

struct argp_option {
	const char *name;
	int key;
	const char *arg;
	int flags; // ignored
	const char *doc;
	int group; // ignored
};

struct argp_child {
};

error_t argp_parse(const struct argp *argp, int argc, char **argv, unsigned flags, int *arg_index, void *input);
void argp_state_help(const struct argp_state *state, FILE *stream, unsigned flags);
void argp_usage(const struct argp_state *state);

#endif
