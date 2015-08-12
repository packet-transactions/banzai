AC_PREREQ([2.61])
AC_INIT([domino], [0.1], [anirudh@csail.mit.edu])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([banzai.cc])
AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])

# Checks for programs.
AC_PROG_CXX

# Add picky CXXFLAGS
CPPFLAGS="-std=c++14 -pthread"
PICKY_CXXFLAGS="-pedantic -Wconversion -Wsign-conversion -Wall -Wextra -Weffc++ -Werror -fno-default-inline"
AC_SUBST([PICKY_CXXFLAGS])

# Checks for header files.
AC_LANG_PUSH(C++)

AC_CHECK_HEADERS([algorithm array cassert cmath queue \
cstdio string sys/stat.h sys/types.h ctime tuple unistd.h unordered_map \
utility vector], [], [AC_MSG_ERROR([Missing header file])])

# C++ libraries are harder to check (http://nerdland.net/2009/07/detecting-c-libraries-with-autotools/),
# so use headers to check

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_LANG_POP(C++)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
