# screentest - Makefile for this robot lib 
NAME = screentest
VERSION = 0.01
LDDIRS = -Llib
PREFIX = /usr/local
LDFLAGS = -lm -ldl -lpthread -lharfbuzz -lbz2 -lbrotlicommon -lbrotlidec -lbrotlienc
IFLAGS = -Ivendor -Iinclude -Iinclude/SDL2 -Iinclude/SDL_ttf
DFLAGS = -DDEBUG
CC = clang
#CC = gcc
CFLAGS = -Wall -Werror -Wno-unused $(IFLAGS)
SRC =
OBJ = ${SRC:.c=.o}
LIBS = lib/libSDL2.a lib/libSDL2_ttf.a lib/libfreetype.a
LPREFIX = $(shell pwd)
PKGSDL = SDL2-2.0.14
COMPANY = ironhead 
ORG = org.$(COMPANY).$(NAME)
ANDDIR = platforms/android
#TARGETS = "build-tools;31.0.0" "cmdline-tools;latest" "platform-tools" "ndk-bundle" "system-images;android-31;default;x86_64
JDKBIN = OpenJDK8U-jdk_x64_linux_hotspot_8u312b07
JDKVER = jdk8u312-b07
#ANDDIR = platforms/org.tubularmodularinc.screentest

# build - Build a C application capable of running on Linux, etc
build: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) src/main.c $(LIBS) $(LDDIRS) $(LDFLAGS) -o bin/$(NAME) && \
		bin/$(NAME)


# android-deps - Build Android dependencies from a working version of the command line tools
# (Note we temporarily set environment variables)
android-deps:
	-mkdir -p share/sdk/cmdline-tools/latest
	-tar -xzf vendor/commandlinetools-linux.tar.gz -C share/sdk/cmdline-tools/
	-tar -xzf vendor/$(JDKBIN).tar.gz -C share/
	export JAVA_HOME=$(PWD)/share/$(JDKVER) && \
	export ANDROID_SDK_ROOT=$(PWD)/share/sdk && \
		$(PWD)/share/sdk/cmdline-tools/latest/bin/sdkmanager --list $(TARGETS)


# sdl-deps - Just unpack SDL and friends
sdl-deps:
	-tar -xzf vendor/$(PKGSDL).tar.gz -C build/SDL


# link-libs - Link a library to the Android (and eventually iOS) folders
link-libs:
	ln -s $(LPREFIX)/build/SDL $(LPREFIX)/platforms/android.including-ttf/app/jni/SDL
	ln -s $(LPREFIX)/build/SDL_ttf $(LPREFIX)/platforms/android.including-ttf/app/jni/SDL_ttf


# link-assets - Link the top-level assets to Android (and eventually iOS) folders
link-assets:
	ln -s $(LPREFIX)/data $(LPREFIX)/platforms/android.including-ttf/app/src/assets


# android - Build an Android version
android:
	cd $(ANDDIR) && ./gradlew build


# android-install - Install a version for Android
android-install:
	cd $(ANDDIR) && ./gradlew installDebug 


# publish - Android
publish:
	cd $(ANDDIR) && find -type f -print0 | xargs -0 sed -i 's/org.libsdl.app/$(ORG)/g;'
	cd $(ANDDIR) && sed -i 's;Game;$(NAME);g' app/src/main/res/values/strings.xml

# resources - create some kind of resources file
resources:
	echo 'Parse a file that contains common resources.'

# explain - List all the targets and what they do
explain:
	@sed -n '/^#/p' Makefile | sed 's/# //' | \
		awk -F - '{ printf "%-12s %s\n", $$1, $$2 }'

# debug - Debug
debug: CFLAGS += -g -fsanitize=address -fsanitize-undefined-trap-on-error $(DFLAGS)
debug: build
	@printf '' >/dev/null


# clean - Remove executable, objects at top-level and any Android/iOS builds
clean:
	-find . -maxdepth 1 -type f -name "*.o" -o -name "$(NAME)" -print0 | \
			xargs -0 rm -f
	-cd $(ANDDIR) && ./gradlew clean 


# clean-deps - Remove dependencies
clean-deps:
	rm -rf share/

aa:
	-cd $(ANDDIR) && ndk-build NDK_PROJECT_PATH=app/ clean 


# pkg - Create a package 
pkg:
	git archive --format tar.gz --prefix $(NAME)-$(VERSION)/ HEAD > /tmp/$(NAME)-$(VERSION).tar.gz


# docs - Create index.html
docs:
	markdown -S README.md > docs/index.html


# Build SDL2 locally
local-build:
	cd vendor/freetype-2.10.4 && \
		./configure --prefix=$(LPREFIX) --with-zlib=no --with-png=no && make && make install


# config - Generate a config file holding all of the environment info
config:
	cp template.env app.env

# deps - Grab any dependencies needed to build on Linux
deps:
	cd vendor/ && \
		wget https://www.libsdl.org/release/$(PKGSDL).tar.gz && \
		tar xf $(PKGSDL).tar.gz && \
		cp -r $(PKGSDL) ../platforms/android-project/app/jni/SDL2
			
.PHONY: build docs


