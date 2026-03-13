# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.71])
AC_INIT([yadkin],[0.07],[ramar@ramarcollins.com])
#AC_CONFIG_SRCDIR([example/config.lua])

# Detect the OS host
AC_CANONICAL_HOST

# Only the Makefile needs to be generated at the moment.
AC_CONFIG_FILES([Makefile,yadkin-init.sh,src/Makefile])

# Define the common program name
progname=yadkin

# Define directories for alternate installation 
#examples="examples"
opersys=
osname=
sharedir=${datarootdir}/${progname}
srcmethod=
srcuri=

# Define company info

# Certtool/certificate stuff (for keystores...)
company=example
#default_certificate_country="US"
#default_certificate_state="NC"
#default_common_name="Antonio R. Collins II"
#default_expiration_days=365
#default_organization="RWK Apps, LLC"
#default_server_ip="127.0.0.1"
#default_server_name="localhost"


# Simple overrides
#AC_ARG_WITH([conf-dir], AS_HELP_STRING([--with-conf-dir=DIR],[Set a different configuration directory]), [confdir=${withval}])

#AC_ARG_WITH([log-dir], AS_HELP_STRING([--with-log-dir=DIR],[Set access and error log directory]), [logdir=${withval}])

AC_ARG_WITH([share-dir], AS_HELP_STRING([--with-share-dir=DIR],[Set a different configuration directory]), [sharedir=${withval}])

AC_ARG_WITH([operating-system], AS_HELP_STRING([--with-operating-system=OSNAME],[Force operating system choice, overriding auto-detection.]), [opersys=${withval}])

AC_ARG_WITH([local-path], AS_HELP_STRING([--with-local-path=DIR],[Define a local path for fetching dependencies (such as Android SDK, etc)]), [srcuri=${withval}; srcmethod='local'])

AC_ARG_WITH([ssh-path], AS_HELP_STRING([--with-ssh-path=DIR],[Define a URI to an SSH server for fetching dependencies (such as Android SDK, etc)]), [srcuri=${withval}; srcmethod='ssh'])

# Utilities to check for
AC_PROG_AWK
AC_PROG_SED
AC_PROG_INSTALL

# Do a custom check for uname 
AC_CHECK_PROG([UNAME],[uname],[yes],[no],,[/usr/bin/uname])

# Do a custom check for gzip
AC_CHECK_PROG([GZIP],[gzip],[yes],[no],,[/usr/bin/gzip])

# Do a custom check for gzip
AC_CHECK_PROG([TAR],[tar],[yes],[no],,[/usr/bin/tar])

# Crude OS detection
#if test -z $opersys
if test 1 -eq 1
then

	case "$host_os" in 
		linux*)
			osname="linux"
		;;
		darwin*)
			osname="macos"
		;;
		cygwin*|mingw*|msys*)
			osname="windows"
		;;
		*)
			AC_MSG_ERROR(["OS $host_os not supported"])	
		;;
	esac

	printf "OS IS $osname\n" > /dev/stderr
fi


# Summary message
cat << EOF

*** yadkin configured with: ***

osname: $osname
sharedir: $sharedir
srcmethod: $srcmethod
srcuri: $srcuri

EOF

# Perform substitutions
AC_SUBST(VERSION)
AC_SUBST(localpath)
AC_SUBST(opersys)
AC_SUBST(osname)
AC_SUBST(sharedir)
AC_SUBST(srcmethod)
AC_SUBST(srcuri)

AC_OUTPUT
