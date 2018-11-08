AC_PREREQ([2.69])
AC_INIT([veoffload-veorun], [1.3.2])
AC_CONFIG_SRCDIR([veorun.c])
AM_INIT_AUTOMAKE([foreign -Wall])

AC_ARG_WITH([release-id], [AS_HELP_STRING([--with-release-id],
                                          [Specify the release ID [1]])],
            [RELEASE=${with_release_id}],
            [RELEASE=1])
AC_SUBST(RELEASE)

# Checks for programs.
AC_PROG_RANLIB
AC_PROG_CC
AM_PROG_AS
AC_PROG_SED
AM_PROG_AR

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h dlfcn.h pthread.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_UINT64_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile debian/Makefile])
AC_OUTPUT
