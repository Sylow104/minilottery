INCLUDE:=$(CURDIR)/include
SRC:=$(CURDIR)/src
BIN:=$(CURDIR)/bin

CFLAGS+=-Wall -I$(INCLUDE)

.PHONY	: all clean

all :
	$(MAKE) $(BIN);
	$(MAKE) $(BIN)/lottery.o

$(BIN)/lottery.o : -lsodium $(wildcard $(SRC)/*.c)
	$(CC) $(CFLAGS) $^ -o $@;

$(BIN)	:
	mkdir -p $@;

clean	: $(BIN)
	rm -r $^
