#ifndef __LIST_OPERATORS__
#define __LIST_OPERATORS__
struct person_list
{
	unsigned int size;
	struct person **array;
};

struct person_list *create_list(unsigned int);
int set_list(struct person_list *);
struct person_list *unset_list();
int destroy_list(struct person_list *);
unsigned int get_list_size();
int add_entry(unsigned int, char *, unsigned int);
int mod_entry(unsigned int, int);
int delete_entry(unsigned int);

int sanitize_list();
int print_list(unsigned int, unsigned int);
#endif

