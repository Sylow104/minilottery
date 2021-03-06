#include "entry.h"
#include "person.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int __rand(unsigned int size);
extern struct person_list *to_operate;

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

int add_entry(unsigned int select, char *n_name,
		unsigned int n_count)
{
	struct person **to_use = get_entry(select);
	if (!to_use) {
		return -1;
	}
	*to_use = create_person(n_name, n_count);
	return 0;
}

struct person *delete_entry(unsigned int select)
{
	struct person **target = get_entry(select), 
		      *to_return, **next_entry;
	if (!target) {
		return 0x0;
	}
	to_return = *target;
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
	return to_return;
}

void random_death(char *name, char *buffer)
{
	const static char *template = "%s %s";
	const static char *list_msgs[] = {
		"was sent to the shadow realm",
		"was yeeted by greg",
		"got killed by a brown fox",
		"got their gear ferghus'd",
		"got doug dimmadome'd",
		"got 3st passworded",
		"was yeeted by girg",
		"dieded",
		"was sent to the mabi gulag"
	};
	static unsigned int previous_value = 10;
	unsigned int select = 0;
	if ((strcmp("energypill", name) == 0)) {
		select = 4;
		goto print;
	} else {
		previous_value = 4;
	}
test:
	select = __rand((sizeof(list_msgs))/(sizeof(char *)));
	if (previous_value == select) {
		goto test;
	} else {
		previous_value = select;
	}
print:
	snprintf(buffer, 64, template, name, list_msgs[select]);
	return;
}

struct person *mod_entry(unsigned int select, int direction)
{
	struct person **to_mod = get_entry(select);
	struct person *to_return = 0x0;
	char message[64];
	char *template;
	if (direction > 0) {
		template = "%s gained a life";
	} else if (direction < 0) {
		template = "%s lost a life";
	} else {
		template = "%s's lives stay constant";
	}
	snprintf(message, 64, template, person_name(*to_mod));
	log_action("mod_entry", message, NONE);
	if (mod_person_count(*to_mod, direction) <= 0) {
		random_death(person_name(*to_mod), message);
		log_action("mod_entry", message, NONE);
		to_return = delete_entry(select);
		print_list(2000, 0);
	} else {
		print_list(1000, 0);
	}
	return to_return;
}


int print_entry(unsigned int select)
{
	struct person **to_print = get_entry(select);
	int size_tab = 0;
	char *name = 0;
	if (!to_print) {
		printf("=No valid entry...=\n");
		return 1;
	}
	name = person_name(*to_print);
	printf("%u %s ", person_count(*to_print), name);
	if ((*to_print)->deadly == true) {
		printf("(deadly) ");
	}
	printf("\n");
	return 0;
}
