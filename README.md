# yadkin

A bootstrapping tool for Android and it's dependencies.

Installing this will allow you to start building Android apps without depending on Android Studio in Linux and Mac OS.  Its goal is to allow for building an Android toolchain with as little interference as possible while stayling light and scriptable.  The tools installed here can be used as a base for cross platform frameworks like SDL or Flutter.  Lastly, it can be used for a CI/CD chain on some other server where tooling like Android Studio cannot be installed easily.


## Use Cases

While this tool may not be 100% useful for those who are purely Android; developers using either Flutter or SDL (or native tools for cross-platform development) should love being able to deploy a valid Android toolkit from the command-line.


## Dependencies

- A Bash shell if you'll only need the Android toolkit.  
- A C Compiler will be needed for the Android application template builder.



## Usage

Running `configure` will build a Makefile suitable for your system.  You can override the default choice by specifying the `--with-operating-system` flag with the symbolic name of your operating system.  (e.g. "linux" if you want a Linux-compatible Makefile, "darwin" if you're on a Mac).

Once that's complete, running `make` will pull down the Java Development Kit, the newest version of Android's command line tools, and the utilities needed to build Android projects from scratch.

If further modification to the install is needed, some helpful `configure` flags you can use are as follows:

Flag | Description
---- | -----------
`--prefix=DIR` | Chooses to install Android SDK and command-line tools under the directory DIR.
`--with-local-path=DIR` | Instead of fetching dependencies over the internet, the installer will search in directory DIR for a Java development kit and the Android command-line tools.
`--with-user=USER` | Defines a specific user to install Yadkin's configuration directory
`--with-group=GROUP` | Defines a specific user to install Yadkin's configuration directory

Additional flags can be viewed by running `./configure --help` in top-level directory of this repository.
