CC = gcc
COMMONFLAGS = -std=c99 -D_POSIX_C_SOURCE=200112L -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat=2 -Wimport -Winit-self -Winline -Winvalid-pch -Wjump-misses-init -Wlogical-op -Werror -Wmissing-declarations -Wpedantic -Wmissing-include-dirs -Wmultichar -Wpacked -Wpointer-arith -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wswitch-default -Wswitch-enum -Wundef -Wvariadic-macros -Wwrite-strings -Wc++-compat -Wdeclaration-after-statement -Wmissing-prototypes -Wnested-externs -Wunused -Wold-style-definition -Wstrict-prototypes
LIBS = -lm
DEBUGFLAGS := $(COMMONFLAGS) -DDEBUG=1 -O -g
RELEASEFLAGS := $(COMMONFLAGS) -fstack-protector-all -O1
SOURCES = RandDotGraph.c
DEPS = RandDotGraph.h

# phony targets
.PHONY: clean release debug all

all: release

release: $(SOURCES) $(DEPS)
	$(CC) $^ $(RELEASEFLAGS) $(LIBS) -o release.out

debug: $(SOURCES) $(DEPS)
	$(CC) $^ $(DEBUGFLAGS) $(LIBS) -o debug.out

clean:
	rm -f *.o *.s *.out *.gch
