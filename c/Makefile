# This file was created on 8 Dec 2025.

# Help from https://www.gnu.org/software/make/manual/make.html

CPPFLAGS += -g -Wall -Werror -Wpedantic

ALL_C_FILES = $(wildcard *.c)

ALL_EXECUTABLE_FILES = tictactoe_main

.PHONY: all
all: $(ALL_EXECUTABLE_FILES)

%.d: %.c
	set -e ; $(RM) $@ ; $(CC) -M $(CPPFLAGS) $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

include $(ALL_C_FILES:.c=.d)

.SECONDEXPANSION:
tictactoe_main: $$@.o tictactoe.o scanf_funcs.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(ALL_EXECUTABLE_FILES) *.o *.d
