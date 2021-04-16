#include "list_operators.h"
#include "person.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static struct person_list *to_operate = 0x0;

struct person **get_array()
{
	if (!to_operate) {
		return 0x0;
	}
	return to_operate->array;
}

struct person **get_entry(unsigned int select) {
	struct person **array_adr = get_array();
	if (!array_adr) {
		return 0x0;
	}
	if (to_operate->size > select && select >= 0) {
		return array_adr + select;
	} else {
		return 0x0;
	}
}

unsigned int get_list_size() {
	if (!to_operate) {
		return 0;
	}
	return to_operate->size;
}

struct person_list *create_list(unsigned int n_entries)
{
	struct person_list *to_ret = (struct person_list*) malloc(
			sizeof(struct person_list));
	if (!to_ret) {
		goto exit;
	}
	to_ret->array = (struct person **) malloc(
			sizeof(struct person *) * n_entries);
	if (!to_ret->array) {
		goto cleanup_n_array;
	}
	to_ret->size = n_entries;
	goto exit;
cleanup_n_array:
	free(to_ret);
exit:
	return to_ret;
}

int set_list(struct person_list *to_use)
{
	if (to_operate) {
		return 1;
	}
	to_operate = to_use;
	return 0;
}

struct person_list *unset_list()
{
	struct person_list *to_return = to_operate;
	to_operate = 0x0;
	return to_return;
}

int destroy_list(struct person_list *to_destroy)
{
	if (!to_destroy) {
		return 1;
	}
	int i;
	for (i = 0; i < to_destroy->size; i++) {
		delete_entry(i);
	}
	free(to_destroy->array);
	free(to_destroy);
	return 0;
}

int sanitize_list()
{
	if (!to_operate) {
		return 1;
	}
	struct person **current;
	for (int i = 0; i < to_operate->size; i++) {
		current = get_entry(i);
		// check if count is zero
		if (!person_count(*current)) {
			printf("Deleting %s\n", person_name(*current));
			delete_entry(i);
			i -= 1;
		}
	}
	printf("List has been sanitized\n");
	print_list(2, 0);
	return 0;
}

int add_entry(unsigned int select, char *n_name,
		unsigned int n_count)
{
	struct person **to_use = get_entry(select);
	if (!to_use) {
		return 1;
	}
	*to_use = create_person(n_name, n_count);
	return 0;
}

int delete_entry(unsigned int select)
{
	struct person **target = get_entry(select), **next_entry;
	if (!target) {
		return -1;
	}
	destroy_person(*target);
	*target = 0x0;
	int i;
	for (i = select; i < (to_operate->size - 1); i++) {
		// get address for next entry
		next_entry = get_entry(i + 1);
		// shifts addresses from next_entry to target
		*target = *next_entry;
		// target gets the address of next_entry for
		// reiteration of loop
		target = next_entry;
	}
	// wipes last address of array as we finished shifting
	*target = 0x0;

	to_operate->size--;
	return select;
}

int mod_entry(unsigned int select, int direction)
{
	struct person **to_mod = get_entry(select);
	if (!to_mod) {
		return 1;
	}
	char *message;
	if (direction > 0) {
		message = "%s gained a life\n";
	} else if (direction < 0) {
		message = "%s lost a life\n";
	} else {
		message = "%s's lives stay constant\n";
	}
	printf(message, person_name(*to_mod));
	if (!mod_person_count(*to_mod, direction)) {
		printf("%s died\n", person_name(*to_mod));
		delete_entry(select);
		print_list(2, 0);
	} else {
		printf("\n");
		print_list(1, 0);
	}
	return 0;
}

int print_entry(unsigned int select)
{
	struct person **to_print = get_entry(select);
	if (!to_print) {
		printf("=No valid entry...=\n");
		return 1;
	}
	printf("++++\nName: %s\nCount: %u\n", person_name(*to_print),
			person_count(*to_print));
	return 0;
}

int print_list(unsigned int time, unsigned int flag)
{
	if (!to_operate) {
		return 1;
	}
	for (int i = 0; i < get_list_size(); i++) {
		print_entry(i);
	}
	if (time > 1) {
		sleep(time);
	} else {
		sleep(1);
	}
	if (!flag) {
		printf("\033c");
	}
	return 0;
}
