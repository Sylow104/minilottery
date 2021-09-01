#include "os.h"
#include <stdio.h>
#include <time.h>

int __sleep(unsigned int miliseconds)
{
#ifdef UNIX
	sleep((miliseconds / 1000));
#else
	Sleep(miliseconds);
#endif
	return 0;
}

int __rand_setup()
{
#ifdef UNIX
	return sodium_init();
#else
	return 0;
#endif
}

unsigned int __rand(unsigned int size)
{
	unsigned int to_ret;
#ifdef UNIX
	static char test_string[32];
	randombytes_buf(test_string, 32);
	to_ret = randombytes_uniform(size);
#else
	static int i = 0;
	srand(time(0x0) + i);
	i = i + 1;
	srand(rand() % size);
	to_ret = rand() % size;
#endif
	return to_ret;
}

int __clear_screen()
{
#ifdef UNIX
	printf("\033c");
#else
	system("cls");
#endif
	return 0;
}