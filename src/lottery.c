#include "lottery.h"
#include <stdio.h>
#include <unistd.h>
#include <sodium.h>

unsigned int winners = 1;
struct person *winner_list = 0x0;

unsigned int random_select(unsigned int size)
{
	char test_string[32];
	randombytes_buf(test_string, 32);
	unsigned int check = randombytes_uniform(size);
	return check;
}

int random_decrement(unsigned int size)
{
	unsigned int rand_int = random_select(size);
	return mod_entry(rand_int, -1);
}

int lottery_runner(struct person_list *lottery_list, unsigned int n_winners)
{
	if (sodium_init() < 0 || set_list(lottery_list)) {
		return 1;
	}
	if (n_winners < 0) {
		log_action("lottery_runner", "I need at least one winner",
				NONE);
		return -1;
	}
	winners = n_winners;
	winner_list = malloc(sizeof(struct person) * winners);

	log_action("lottery_runner", "Welcome to the lottery program!",
			NONE);
#ifdef DEBUG
	sleep(1);
#endif
	printf("\033c");
	sanitize_list();
	unsigned int size = get_list_size();
	do {
		random_decrement(size);
		size = get_list_size();
	} while (size > 1);
	printf("\033c");
	printf("Winner of the lottery:\n");
	print_list(5, 1);
	printf("Thank you for all playing!\n");
cleanup:
	unset_list();
	free(winner_list);
	return 0;
}
