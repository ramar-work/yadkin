# yadkin

A bootstrapping tool for Android and it's dependencies.

Installing this will allow you to start building Android apps without dependence on Android Studio on Linux and Mac OS.  Its goal is to allow for building an Android toolchain with as little interference as possible while stayling light and scriptable.  The tools installed here can be used as a base for cross platform frameworks like SDL or Flutter.  Lastly, it can be used for a CI/CD chain on some other server where tooling like Android Studio cannot be installed.


## Dependencies

A Bash shell if you'll only need the Android toolkit.  A C Compiler will be needed for the Android application template builder.


## Usage

Running `configure` will (attempt to) build a Makefile suitable for your system.  You can override the default choice by specifying the --ostype flag with the symbolic name of your OS.  (e.g. "linux" if you want a Linux compatible Makefile).

Once that's complete, running `make` will pull down the Java Development Kit, the newest version of Android's command line tools, and the utilities for building Android projects from scratch.   NOTE: If you wish to disable any of these features, do so from the `configure` script in the top-level of this repository.  You won't have to mess with the Makefile this way and will save some frustration.
