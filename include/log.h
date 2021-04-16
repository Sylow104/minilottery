#ifndef _LOG_
#define _LOG_
#include <stdio.h>
#include <stdlib.h>

enum verbosity_e
{
	NONE,
	RESULTS,
	I_DEBUG
};

void log_setup(enum verbosity_e log_level);
void log_action(char *function, char *message, enum verbosity_e min_level);
void log_shutdown();
#endif
