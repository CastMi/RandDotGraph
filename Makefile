CC = gcc 
COMMONFLAGS = -std=c99 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat=2 -Wimport -Winit-self -Winline -Winvalid-pch -Wjump-misses-init -D_POSIX_C_SOURCE=200112L -Wlogical-op -Werror -Wmissing-declarations -Wpedantic -Wmissing-include-dirs -Wmultichar -Wpacked -Wpointer-arith -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wswitch-default -Wswitch-enum -Wundef -Wvariadic-macros -Wwrite-strings -Wc++-compat -Wdeclaration-after-statement -Wmissing-prototypes -Wnested-externs -Wunused -Wold-style-definition -Wstrict-prototypes
LIBS = -lm 
DEBUGLAGS := $(COMMONFLAGS) -DDEBUG=1 -Og
RELEASEFLAGS := $(COMMONFLAGS) -fstack-protector-all -O3
SOURCES = RandDotGraph.c
DEPS = RandDotGraph.h

# phony targets
.PHONY: clean release debug all

all: release

release: $(SOURCES) $(DEPS)
	$(CC) $^ $(COMMONFLAGS) $(RELEASEFLAGS) $(LIBS) -o release.out

debug: $(SOURCES) $(DEPS)
	$(CC) $^ $(COMMONFLAGS) $(DEBUGLAGS) $(LIBS) -o debug.out

clean:
	rm -f *.o *.s *.out *.gch debug.out release.out

