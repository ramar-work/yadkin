# yadkin - Makefile for packaging Android
NAME = yadkin
VERSION = 0.04
PREFIX = /opt/$(NAME)
BRANCH = linux
SRCURL = yadkin.ironhead.io
HTTPSRC = http://$(SRCURL)
REPOSRC = git://$(SRCURL)
PKGSDL = SDL2-2.0.14
COMPANY = ironhead 
ORG = org.$(COMPANY).$(NAME)
TARGETS = "build-tools;31.0.0" "cmdline-tools;latest" "platform-tools" "ndk-bundle" "system-images;android-31;default;x86_64"
CLITOOLS = commandlinetools-$(BRANCH).tar.gz 
JDKBIN = OpenJDK8U-jdk_x64_$(BRANCH)_hotspot_8u312b07
JDKVER = jdk8u312-b07


# main - The primary target should just unpack deps (if needed), and download everything 
#	test -d vendor || git clone $(REPOSRC)/yadkind.git -b $(BRANCH) --single-branch vendor
main:
	-mkdir -p ./share/sdk/cmdline-tools/latest
	-tar -xzf vendor/$(CLITOOLS) -C share/sdk/cmdline-tools/
	-tar -xzf vendor/$(JDKBIN).tar.gz -C share/
	export JAVA_HOME=./share/$(JDKVER) && \
	export ANDROID_SDK_ROOT=./share/sdk && \
		./share/sdk/cmdline-tools/latest/bin/sdkmanager $(TARGETS)



# install - Install
install:
	mkdir -p $(PREFIX)/bin/
	mkdir -p $(PREFIX)/etc/$(NAME)/
	mkdir -p $(PREFIX)/include/$(NAME)/
	mkdir -p $(PREFIX)/share/
	mv share $(PREFIX)/share/$(NAME)
	mkdir -p $(PREFIX)/share/$(NAME)/images/
	ln -s $(PREFIX)/share/$(NAME)/$(JDKVER)/bin/java $(PREFIX)/bin/
	ln -s $(PREFIX)/share/$(NAME)/$(JDKVER)/bin/keytool $(PREFIX)/bin/
	ln -s $(PREFIX)/share/$(NAME)/sdk/platform-tools/adb $(PREFIX)/bin/
	ln -s $(PREFIX)/share/$(NAME)/sdk/emulator/emulator $(PREFIX)/bin/
	test -d /etc/zsh/ || mkdir -p /etc/zsh/
	test -d /etc/profile.d/ || mkdir -p /etc/profile.d/
	cp environment/unix.env /etc/profile.d/$(NAME).sh
	cp environment/unix.env /etc/zsh/$(NAME).zsh
	echo "$(NAME) installed successfully, please restart your terminal or system for PATH changes to take effect."


# android-sdkup - Get a sensible Android build tool and SDK combination
# 	(The one specified here will run with Flutter.)
android-sdkup:
	sdkmanager "platform-tools" "platforms;android-29" "build-tools;28.0.3"


# android-device - Build a new Android device
android-device:
	export JAVA_HOME=$(PREFIX)/share/yadkin/$(JDKVER) && \
	export ANDROID_SDK_ROOT=$(PREFIX)/share/yadkin/sdk && \
	avdmanager create avd \
			-n ironhead_test \
			-k "system-images;android-31;default;x86_64" \
			-p /opt/yadkin/share/images


# android-nexus6p - Another random image...
android-nexus6p: DEVICE_NAME=nexus6p
android-nexus6p:
	avdmanager create avd \
		--force \
		--name $(DEVICE_NAME) \
		--abi default/x86_64 \
		--package "system-images;android-31;default;x86_64" \
		--path /opt/yadkin/share/yadkin/images/$(DEVICE_NAME).avd \
		--device "Nexus 6P"


# android-checkaccel - Check for acceleration capabilities
android-checkaccel:
	emulator -accel-check


# android-startnexus6p - Start the Nexus 6p image
android-startnexus6p: DEVICE_NAME=nexus6p
android-startnexus6p:
	emulator \
		-avd $(DEVICE_NAME) \
		-accel on

image:
	cd $(PREFIX)/share/yadkin/sdk/cmdline-tools/latest/bin/ && \
		cmd /c avdmanager.bat --verbose create avd \
			--force -d 18 -n yadkin_pixel_3 -k "system-images;android-31;default;x86_64" -p `cygpath -w $(PREFIX)/share/images`

	
image-list:
	cd $(PREFIX)/share/yadkin/sdk/cmdline-tools/latest/bin/ && \
		cmd /c avdmanager.bat list

	
image-help:
	cd $(PREFIX)/share/yadkin/sdk/cmdline-tools/latest/bin/ && \
		cmd /c avdmanager.bat create avd --help 


# example-sdl-app


# example-android-app


# example-iphone-app


# sdl-deps - Just unpack SDL and friends
sdl-deps:
	-tar -xzf vendor/$(PKGSDL).tar.gz -C build/SDL


# explain - List all the targets and what they do
explain:
	@sed -n '/^#/p' Makefile | sed 's/# //' | \
		awk -F - '{ printf "%-12s %s\n", $$1, $$2 }'


# clean - Remove dependencies
clean:
	rm -rf share/


# docs - Create index.html
docs:
	markdown -S README.md > docs/index.html


.PHONY: build docs

