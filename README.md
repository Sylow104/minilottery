# mini-lotto
for doing giveaways with a random number generator

# requires
- libsodium 1.0.18-3
- gcc 10.2.1
- gnu make 4.2.1
this works on fedora 32, kernel 5.xx

# installation
run `make` in the root directory where MAKEFILE is

# cleanup
run `make clean` to clean up files

# todo
- ~~add arguments to accept .txt files~~
- ~~implement a faster prng at run-time with random seed~~
- ~~check file and remove any invalid entries upon scanning~~
