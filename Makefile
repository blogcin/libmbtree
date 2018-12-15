CC ?= gcc
AR ?= ar
PWD := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
OUT := $(PWD)build

all: libmbtree

libmbtree: libmbtree.c
			 mkdir -p $(OUT)
			 $(CC) -c -fPIC -o $(OUT)/$@.o $<
			 $(CC) $(OUT)/libmbtree.o -shared -o $(OUT)/lib$@.so
clean:
			 rm -f *.o *.a *.so
			 rm -rf $(OUT)
