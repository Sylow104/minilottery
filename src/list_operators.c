#include "list_operators.h"
#include "person.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct person_list *to_operate = 0x0;

struct person **get_array()
{
	if (!to_operate) {
		return 0x0;
	}
	return to_operate->array;
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
	log_action("create_list", "Created person list", I_DEBUG);
	goto exit;
cleanup_array:
	free(to_ret->array);
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
	log_action("destroy_list", "Destroyed the target list", I_DEBUG);
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
	log_action("sanitize_list", "List has been sanitized", NONE);
	print_list(2, 0);
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
#ifndef DEBUG
	if (time > 1) {
		sleep(time);
	} else {
		sleep(1);
	}
	if (!flag) {
		printf("\033c");
	}
#endif
	return 0;
}
