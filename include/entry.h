#ifndef __ENTRY__
#define __ENTRY__
#include "person.h"
#include "list_operators.h"

#define TABSIZE	8

struct person **get_entry(unsigned int);
int add_entry(unsigned int, char *, unsigned int);
struct person *mod_entry(unsigned int, int);
struct person *delete_entry(unsigned int);
int print_entry(unsigned int);

#endif

