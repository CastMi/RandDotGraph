AC_INIT([RandDotGraph],[0.1])

AC_CONFIG_MACRO_DIR([m4])
# This is the version I have installed in my system but if you are able to
# execute with an older version (very likely) please update this numbers.
AM_INIT_AUTOMAKE([-Wall -Werror foreign 1.14 subdir-objects])
# As above.
AC_PREREQ([2.69])

AC_USE_SYSTEM_EXTENSIONS
AC_LANG([C])
# Checks for programs.
LT_INIT
AC_PROG_CC_C99
AC_PROG_CC
AC_FUNC_MALLOC
AC_FUNC_STRERROR_R
AC_FUNC_STRNLEN

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG,
	AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
	AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
