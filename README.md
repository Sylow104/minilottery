# minilottery
for doing giveaways with a random number generator

# requires
- libsodium 1.0.18-3
- cmake +3.10 or higher
- a C compiler

# installation
create a `build` directory, change into it, run `cmake ../`, followed by
`make`. optionally, run `make install` to install to system.

run `make package` to create binary distributables for your system. edit
`CMakeLists.txt` under the variable `CPACK_GENERATOR` to your needs.

# cleanup
run `make clean` to clean up files

# todo
- ~~add arguments to accept .txt files~~
- ~~implement a faster prng at run-time with random seed~~
- ~~check file and remove any invalid entries upon scanning~~
- export results in a text file.
