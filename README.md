# yadkin

A bootstrapping tool for Android and it's dependencies.

Installing this will allow to start building Android apps with little issue on Linux, Mac OS or Windows.  Its goal is to allow for building an Android toolchain with as little interference as possible while stayling light and scritable.  

Primary uses for this toolchain are used with something like Flutter, for instance, to setup tools like the Android debugger, emulator and more.  It can also be used as a base for other cross platform tooling, like SDL.  Lastly, it can be used for a CI/CD chain on some other server where tooling like Android Studio cannot be installed.


## Dependencies

A Bash shell if you'll only need the Android toolkit.  A C Compiler will be needed for the Android application template builder.


## Usage

Running `make` with the target of your choice as an argument will pull down the JDK and the newest version of Android's command line tools.  Configuration of paths and versions can be done from the Makefile. 

