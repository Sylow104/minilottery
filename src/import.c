#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person_list *import_list(const char *filename)
{
	struct person_list *to_ret = 0x0;
	FILE *to_read = fopen(filename, "r");
	if (!to_read) {
		goto exit;
	}
	const char *format = "%s\t%u\n";
	char *new_name = (char *) malloc(sizeof(char) * 32);
	if (!new_name) {
		goto exit;
	}

	// count the size of the data entries
	unsigned int new_count, size = 0;
	while (fscanf(to_read, format, new_name, &new_count) != EOF) {
		size++;
	}
	// rewind
	fseek(to_read, 0, SEEK_SET);
	to_ret = create_list(size);
	if (!to_ret) {
		goto exit;
	} else {
		set_list(to_ret);
	}
	// write the list to the array
	for (int i = 0; i < get_list_size(); i++) {
		fscanf(to_read, format, new_name, &new_count);
		add_entry(i, new_name, new_count);
		memset(new_name, 0, 32);
	}
cleanup:
	free(new_name);
	to_ret = unset_list();
	fclose(to_read);
exit:
	return to_ret;
}
