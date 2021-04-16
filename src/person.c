#include "person.h"
#include <stdlib.h>
#include <string.h>

struct person *create_person(const char *name, unsigned int count)
{
	struct person *to_ret = (struct person*) malloc(sizeof(struct person));
	if (!to_ret) {
		log_action("create_person",
				"Unable to create a person.", NONE);
		goto exit;
	}
	to_ret->name = (char *) malloc(strlen(name) + 1);
	strcpy(to_ret->name, name);
	to_ret->count = count;
	
exit:
	return to_ret;
}

int destroy_person(struct person *to_destroy)
{
	int ret_code = 1;
	if (!to_destroy) {
		goto exit;
	}
	if (to_destroy->name) {
		free(to_destroy->name);
	}
	free(to_destroy);
	ret_code = 0;

exit:
	return ret_code;
}

int mod_person_count(struct person *to_mod, int to_add)
{
	to_mod->count += to_add;
	return (to_mod->count);
}

unsigned int person_count(struct person *to_print)
{
	return to_print->count;
}

char *person_name(struct person *to_print)
{
	return to_print->name;
}
