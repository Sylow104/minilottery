#include "lottery.h"
#include "person.h"
#include <stdio.h>
#ifdef UNIX
#include <sodium.h>
#include <math.h>
#endif
#include <time.h>

unsigned int winners = 1;
unsigned int winslots = 1;
struct person **winner_list = 0x0;

unsigned int random_select(unsigned int size)
{
	static int i = 0;
#ifdef UNIX
	static char test_string[32];
	randombytes_buf(test_string, 32);
	unsigned int check = randombytes_uniform(size);
#else
	srand(time(0x0) + i);
	i = i + 1;
	srand(rand() % size);
	unsigned int check = rand() % size;
#endif
	return check;
}

int random_decrement(unsigned int size)
{
	unsigned int rand_int = random_select(size);
	struct person *holder = mod_entry(rand_int, -1);
	if (holder) {
		if (size > winners) {
			destroy_person(holder);
		} else if (size <= winslots) {
			*(winner_list + winslots - 1) = holder;
			winslots--;
		}
	}
	return 0;
}

int lottery_runner(struct person_list *lottery_list, unsigned int n_winners)
{
	int i = 0;
#ifdef UNIX
	if (sodium_init() < 0 || set_list(lottery_list)) {
		return 1;
	}
#else
	if (set_list(lottery_list)) {
		return 1;
	}
#endif
	if (n_winners < 0) {
		log_action("lottery_runner", "I need at least one winner",
				NONE);
		return -1;
	}
	if (n_winners > get_list_size()) {
		winners = get_list_size();
	} else {
		winners = n_winners;
	}
	winslots = winners;
	winner_list = malloc(sizeof(struct person *) * winners);

	log_action("lottery_runner", "Welcome to the lottery program!",
			NONE);
#ifndef DEBUG
	sleep(1);
	printf("\033c");
#endif
	sanitize_list();
	unsigned int size = get_list_size();
	do {
		random_decrement(size);
		size = get_list_size();
	} while (size > 1);
	*(winner_list) = *get_entry(0);
#ifndef DEBUG
	printf("\033c");
#endif
	log_action("lottery_runner", "Winner(s) of the lottery:", NONE);
	char message[64];
	for (i = 0; i < winners; i++) {
		snprintf(message, 64, "%d %s", i + 1, 
				person_name(*(winner_list + i)));
		log_action("lottery_runner", message, NONE);
	}
	printf("Thank you for all playing!\n");
cleanup:
	unset_list();
	for (i = 0; i < winners; i++) {
		destroy_person(*(winner_list + i));
	}
	free(winner_list);
	return 0;
}
