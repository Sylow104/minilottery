#include "log.h"

static FILE *log_file = 0x0;
static enum verbosity_e log_level = NONE;

void log_setup(enum verbosity_e n_log_level)
{
	log_level = n_log_level;
	if (log_level >= RESULTS) {
		log_file = fopen("log.txt", "w");
		if (!log_file) {
			printf("Fatal! Cannot write log file!\n");
			abort();
		}
		log_action("log_setup", "Logger has started.", I_DEBUG);
	}
	return;
}

void log_shutdown()
{
	log_action("log_shutdown", "Shutting down logger.", I_DEBUG);
	fclose(log_file);
	return;
}

void log_action(char *function, char *message, enum verbosity_e min_level)
{
	FILE *direction = stdout;
	if (log_level >= min_level) {
double_take:
		if (!function || log_level >= I_DEBUG) {
			fprintf(direction, "%s: ", function);
		}
		fprintf(direction, "%s \n", message);
		if (direction != log_file && log_level >= RESULTS) {
			direction = log_file;
			goto double_take;
		}
	}
exit:
	return;
}
