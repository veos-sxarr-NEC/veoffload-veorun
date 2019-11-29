AC_PREREQ([2.69])
AC_INIT([veoffload-veorun], [2.2.2])
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
AC_SUBST(CCLD)
AM_PROG_CC_C_O
AM_PROG_AS
AC_PROG_SED
AM_PROG_AR
AC_PROG_LN_S

# Checks for libraries.
AC_SEARCH_LIBS([dlopen], [dl], [], [
  AC_MSG_ERROR([dlopen() is not found])
])
AC_SEARCH_LIBS([pthread_create], [pthread], [], [
  AC_MSG_ERROR([pthread_create() is not found])
])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h dlfcn.h pthread.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_UINT64_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile debian/Makefile])
AC_OUTPUT
