#include "person.h"
#include <stdlib.h>
#include <string.h>

int max_char_len = 0;

int largest_8(int input)
{
	int output = 0;
	output = ((input / TABSIZE) + (input % TABSIZE)) * TABSIZE;
	return output;
}

struct person *create_person(const char *name, unsigned int count)
{
	int cur_char_len = 0;
	char message[64];
	struct person *to_ret = (struct person*) malloc(sizeof(struct person));
	if (!to_ret) {
		log_action("create_person",
				"Unable to create a person.", I_DEBUG);
		goto exit;
	}
	cur_char_len = strlen(name);
	if (cur_char_len > max_char_len) {
		max_char_len = largest_8(cur_char_len);
		snprintf(message, 64, "updated largest max char: %d",
				max_char_len);
		log_action("create_person", message, I_DEBUG);
	}
	to_ret->name = (char *) malloc(cur_char_len + 1);
	strcpy(to_ret->name, name);
	to_ret->count = count;
	log_action("create_person", "Created person", I_DEBUG);
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
	log_action("destroy_person", "Destroyed person", I_DEBUG);
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
