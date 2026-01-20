# This file was created on 25 Dec 2025.

# Help from https://www.gnu.org/software/make/manual/make.html

CPPFLAGS += -g -Wall -Werror -Wpedantic

ALL_CPP_FILES = $(wildcard *.cpp)

ALL_EXECUTABLE_FILES = tictactoe_main

.PHONY: all
all: $(ALL_EXECUTABLE_FILES)

%.d: %.cpp
	set -e ; $(RM) $@ ; $(CXX) -M $(CPPFLAGS) $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

include $(ALL_CPP_FILES:.cpp=.d)

.SECONDEXPANSION:
tictactoe_main: $$@.o tictactoe.o scanf_funcs.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(ALL_EXECUTABLE_FILES) *.o *.d
