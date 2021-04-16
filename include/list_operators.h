#ifndef __LIST_OPERATORS__
#define __LIST_OPERATORS__
#include "person.h"
#include "entry.h"
struct person_list
{
	unsigned int size;
	struct person **array;
};

struct person **get_array();
struct person_list *create_list(unsigned int);
int set_list(struct person_list *);
struct person_list *unset_list();
int destroy_list(struct person_list *);
unsigned int get_list_size();

int sanitize_list();
int print_list(unsigned int, unsigned int);
#endif

