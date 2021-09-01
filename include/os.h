#ifndef _OS_
#define _OS_

#ifdef UNIX
#include <unistd.h>
#include <sodium.h>
#else
#include <Windows.h>
#endif

int __sleep(unsigned int miliseconds);
int __rand_setup();
unsigned int __rand(unsigned int size);
int __clear_screen();
#endif /* _OS_ */