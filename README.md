# minilottery
for doing giveaways with a random number generator

# requires
- a C compiler
- cmake +3.10 or higher
## linux
- libsodium 1.0.18-3

# installation
there are two different releases, `DEBUG` and `RELEASE`.
## vs code
with the CMake extension, configure and build should work out of the box (TODO: add more descriptions here)
## linux
create a directory called `build` and `cd` into it. call `cmake ../`, then invoke `make`.

# usage
`./minilottery <FILENAME>`, where `<FILENAME>` are tabbed delimited entries. each entry should be formatted as
```
<NUMBER OF POINTS>\t<NAME>\n
```
where `\t` and `\n` denote tab and newline.

# todo
- add flags to modify flag values (debug, number of winners, etc).
- ~~clean up code, make portable for Windows usage.~~