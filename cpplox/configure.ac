AC_INIT([cpplox], [0.0.1])

AC_CONFIG_SRCDIR([src/Lox.cpp])

AC_PROG_CC
AC_PROG_RANLIB

AC_LANG([C++])

AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

AC_CHECK_HEADERS([cstddef])
AC_CHECK_HEADERS([cstdint])
AC_CHECK_HEADERS([cctype])

AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([vector])
AC_CHECK_HEADERS([unordered_map])
AC_CHECK_HEADERS([utility])

AC_CHECK_HEADERS([log/Log.h])
AC_CHECK_HEADERS([scanner/Scanner.h])
AC_CHECK_HEADERS([scanner/Token.h])

AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile
  src/module.mk
  lib/log/module.mk
  lib/scanner/module.mk])

AC_OUTPUT
