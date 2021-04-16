#ifndef __PERSON__
#define __PERSON__
#include "log.h"

struct person
{
	char *name;
	unsigned int count;
};

int print_person(struct person *);
int destroy_person(struct person *);
struct person *create_person(const char *, unsigned int);
int mod_person_count(struct person *, int);
unsigned int person_count(struct person *);
char *person_name(struct person *);
#endif
