CC	?= cc
CFLAGS	?= -Wall -Wextra -pedantic -g -O2 -std=c99

%: %.o
	@echo "	LINK $<"
	@$(CC) -o $@ $+ $(LDFLAGS)

%.o: %.c
	@echo "	CC $<"
	@$(CC) -c $< $(CFLAGS)

all: hw2.out
hw2: extras.o 