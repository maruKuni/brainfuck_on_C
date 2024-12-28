CC:=clang
# CFLAGS+=-fsanitize=address
# CFLAGS+=-g
CFLAGS+=-O3

vpath %.c src
vpath %.o obj

INCLUDE:=-Iinclude

.PHONY: all clean

all:bin/brainfuck.exe

SRCS:=$(wildcard src/*.c)
OBJS:=$(SRCS:src/%.c=obj/%.o)

$(OBJS):obj/%.o:src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o  $@ $<

bin/brainfuck.exe:$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	-rm obj/*.o
	-rm bin/*.exe