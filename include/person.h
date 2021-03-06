#ifndef __PERSON__
#define __PERSON__
#include "log.h"
#include <stdbool.h>

#define TABSIZE 8
#ifndef _MAX_CHAR_
extern int max_char_len;
#endif

struct person
{
	bool deadly;
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
