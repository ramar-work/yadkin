# 
CC=gcc
CC=clang
CFLAGS=-Wall -Werror -Wno-unused -Ivendor
PREFIX=/usr/local
BIN=yadkin

main: zrender.o ztable.o zwalker.o
	$(CC) $(CFLAGS) -lm $^ main.c -o ../$(BIN)

debug: CC=clang
debug: CFLAGS+=-g -DDEBUG_H -fsanitize=address
debug: zrender.o ztable.o zwalker.o
	$(CC) -g $(CFLAGS) -lm $^ main.c -o ../bin/$(BIN)

lua:
	cd vendor/lua-5.4.3 && make && cp src/liblua.a ../../	

install:
	cp bin/$(BIN) $(PREFIX)/bin/

clean:
	find . -type f -name "*.o" | xargs rm
