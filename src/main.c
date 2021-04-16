#include "main.h"
#include <stdio.h>

int main(int argc, const char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <filename>\n", *(argv));
		return -1;
	}
	struct person_list *to_import = import_list(*(argv + 1));
	if (!to_import) {
		printf("Cannot find file %s. Exiting.\n", *(argv + 1));
		return -1;
	}
	lottery_runner(to_import);

	return destroy_list(to_import);
}
