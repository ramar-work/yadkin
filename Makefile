# screentest - Makefile for this robot lib 
NAME = screentest
VERSION = 0.01
LDDIRS = -Llib
PREFIX = /usr/local
LDFLAGS = -lm -ldl -lpthread -lharfbuzz -lbz2 -lbrotlicommon -lbrotlidec -lbrotlienc
IFLAGS = -Ivendor -Iinclude
DFLAGS = -DDEBUG
CC = clang
#CC = gcc
CFLAGS = -Wall -Werror -Wno-unused $(IFLAGS)
SRC =
OBJ = ${SRC:.c=.o}
LIBS = lib/libSDL2.a lib/libSDL2_ttf.a lib/libfreetype.a
LPREFIX = $(shell pwd)

# android - Build an android version
android:
	cd platforms/android-project/ && ./gradlew build


# build - Build the basic version of this tool
build: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) src/main.c \
		$(LIBS) $(LDDIRS) $(LDFLAGS) -o bin/$(NAME)



# android-install - Install a version for Android
android-install:
	cd platforms/android-project/ && ./gradlew installDebug 


# explain - List all the targets and what they do
explain:
	@sed -n '/^#/p' Makefile | sed 's/# //' | \
		awk -F - '{ printf "%-12s %s\n", $$1, $$2 }'


# debug - Debug
debug: CFLAGS += -g -fsanitize=address -fsanitize-undefined-trap-on-error $(DFLAGS)
debug: build
	@printf '' >/dev/null


# clean - Clean up everything
clean:
	-rm $(NAME)
	-find -type f -name "*.o" -print0 | xargs -0 rm -f 
	-find ./platforms/android-project/app/build/ -type f -name "*.so" | xargs rm


# pkg - Create a package 
pkg:
	git archive --format tar.gz --prefix $(NAME)-$(VERSION)/ HEAD > /tmp/$(NAME)-$(VERSION).tar.gz


# docs - Create index.html
docs:
	markdown -S README.md > index.html


# Build SDL2 locally
local-build:
	cd vendor/freetype-2.10.4 && \
		./configure --prefix=$(LPREFIX) --with-zlib=no --with-png=no && make && make install


# deps - Grab any dependencies needed to build on Linux
deps:
	wget https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
