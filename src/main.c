#include "main.h"
#include <stdio.h>

int main(int argc, const char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <filename>\n", *(argv));
		return -1;
	}
	log_setup(RESULTS);
	struct person_list *to_import = import_list(*(argv + 1));
	if (!to_import) {
		return -1;
	}
	lottery_runner(to_import, 4);
	destroy_list(to_import);
	log_shutdown();
}
