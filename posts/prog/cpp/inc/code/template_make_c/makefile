#
# Makefile: main makefile
# Author: Mike Chang
#

CC:=gcc
LD:=ld
CFLAGS:=-g
LFLAGS:=-lm -lrt -lpthread -Llib -ltest
OUT_FILE:=out

src:=$(wildcard *.c)
src+=$(wildcard $(addsuffix *.c, $(wildcard */)))
objdir:=objects $(addprefix objects/, $(wildcard */))
objs:=$(addprefix objects/, $(patsubst %.c, %.o, $(subst ./,,$(src))))
CFLAGS+=$(addprefix -I, $(wildcard */))

all: create_bin

create_bin: $(objs)
	$(CC) $(CFLAGS) $^ -o $(OUT_FILE) $(LFLAGS)

$(objs): objects/%.o: %.c
	@mkdir -p $(objdir)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm $(objdir) -rf
