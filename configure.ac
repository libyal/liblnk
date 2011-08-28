AC_PREREQ( 2.59 )

AC_INIT(
 [liblnk],
 [20110828],
 [jbmetz@users.sourceforge.net])

AC_CONFIG_SRCDIR(
 [include/liblnk.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
COMMON_ARG_ENABLE(
 [wide-character-type],
 [wide_character_type],
 [enable wide character type support],
 [no])
COMMON_ARG_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [auto-detect])
COMMON_ARG_ENABLE(
 [static-executables],
 [static_executables],
 [build the lnktools as static executables],
 [no])
COMMON_ARG_ENABLE(
 [verbose-output],
 [verbose_output],
 [enable verbose output],
 [no])
COMMON_ARG_ENABLE(
 [debug-output],
 [debug_output],
 [enable debug output],
 [no])

COMMON_ARG_WITH(
 [libuna],
 [libuna],
 [search for libuna in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
COMMON_ARG_WITH(
 [libbfio],
 [libbfio],
 [search for libbfio in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
COMMON_ARG_WITH(
 [libfdata],
 [libfdata],
 [search for libfdata in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
COMMON_ARG_WITH(
 [libfdatetime],
 [libfdatetime],
 [search for libfdatetime in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
COMMON_ARG_WITH(
 [libfguid],
 [libfguid],
 [search for libfguid in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
COMMON_ARG_WITH(
 [libfvalue],
 [libfvalue],
 [search for libfvalue in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])
dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_VOLATILE

dnl Automatically enable winapi support for mingw
AC_CHECK_WINAPI

dnl Check for type definitions
AC_CHECK_LOCAL_TYPES

dnl Check for headers

dnl Check for functions

dnl Check for internationalization functions in libesedb/libesedb_i18n.c 
AC_CHECK_FUNCS([bindtextdomain])

dnl Check for printf conversion specifier support
AC_CHECK_FUNC_PRINTF_JD
AC_CHECK_FUNC_PRINTF_ZD

dnl Checks for libraries and library functions
dnl ac_libesedb_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_CHECK_LOCAL_COMMON
AC_CHECK_LOCAL_LIBCSTRING
AC_CHECK_LOCAL_LIBERROR
AC_CHECK_LOCAL_LIBNOTIFY
AC_CHECK_LOCAL_LIBSYSTEM

dnl Check for enabling libuna for Unicode string support
AC_CHECK_LIBUNA

AS_IF(
 [test "x$ac_cv_libuna" = xyes],
 [AC_SUBST(
  [libesedb_pc_libs_private_libuna],
  [-luna])
 ])

AS_IF(
 [test "x$ac_cv_libuna" = xyes],
 [AC_SUBST(
  [libesedb_spec_requires_libuna],
  [libuna])
 AC_SUBST(
  [libesedb_spec_build_requires_libuna],
  [libuna-devel])
 ])

AS_IF(
 [test "x$ac_cv_libuna" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBUNA],
  [1],
  [Define to 1 if the local version of libuna is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBUNA],
  [1])
 AC_SUBST(
  [LIBUNA_CPPFLAGS],
  [-I../libuna])
 AC_SUBST(
  [LIBUNA_LIBADD],
  [../libuna/libuna.la])
 ac_cv_libuna=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBUNA],
 [test "x$ac_cv_libuna" = xlocal])

dnl Check for enabling libbfio for basic file IO support
AC_CHECK_LIBBFIO

AS_IF(
 [test "x$ac_cv_libbfio" = xyes],
 [AC_SUBST(
  [libesedb_pc_libs_private_libbfio],
  [-lbfio])
 ])

AS_IF(
 [test "x$ac_cv_libbfio" = xyes],
 [AC_SUBST(
  [libesedb_spec_requires_libbfio],
  [libbfio])
 AC_SUBST(
  [libesedb_spec_build_requires_libbfio],
  [libbfio-devel])
 ])

AS_IF(
 [test "x$ac_cv_libbfio" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBBFIO],
  [1],
  [Define to 1 if the local version of libbfio is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBBFIO],
  [1])
 AC_SUBST(
  [LIBBFIO_CPPFLAGS],
  [-I../libbfio])
 AC_SUBST(
  [LIBBFIO_LIBADD],
  [../libbfio/libbfio.la])
 ac_cv_libbfio=local
 ])

AS_IF(
 [test "x$ac_cv_libbfio" = xlocal],
 [AC_CHECK_LOCAL_LIBBFIO])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBBFIO],
 [test "x$ac_cv_libbfio" = xlocal])

dnl Check for enabling libfdatetime for file date and time support
AC_CHECK_LIBFDATETIME

AS_IF(
 [test "x$ac_cv_libfdatetime" = xyes],
 [AC_SUBST(
  [libesedb_pc_libs_private_libfdatetime],
  [-lfdatetime])
 ])

AS_IF(
 [test "x$ac_cv_libfdatetime" = xyes],
 [AC_SUBST(
  [libesedb_spec_requires_libfdatetime],
  [libfdatetime])
 AC_SUBST(
  [libesedb_spec_build_requires_libfdatetime],
  [libfdatetime-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfdatetime" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFDATETIME],
  [1],
  [Define to 1 if the local version of libfdatetime is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFDATETIME],
  [1])
 AC_SUBST(
  [LIBFDATETIME_CPPFLAGS],
  [-I../libfdatetime])
 AC_SUBST(
  [LIBFDATETIME_LIBADD],
  [../libfdatetime/libfdatetime.la])
 ac_cv_libfdatetime=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFDATETIME],
 [test "x$ac_cv_libfdatetime" = xlocal])

dnl Check for enabling libfguid for file GUID/UUID support
AC_CHECK_LIBFGUID

AS_IF(
 [test "x$ac_cv_libfguid" = xyes],
 [AC_SUBST(
  [libesedb_pc_libs_private_libfguid],
  [-lfguid])
 ])

AS_IF(
 [test "x$ac_cv_libfguid" = xyes],
 [AC_SUBST(
  [libesedb_spec_requires_libfguid],
  [libfguid])
 AC_SUBST(
  [libesedb_spec_build_requires_libfguid],
  [libfguid-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfguid" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFGUID],
  [1],
  [Define to 1 if the local version of libfguid is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFGUID],
  [1])
 AC_SUBST(
  [LIBFGUID_CPPFLAGS],
  [-I../libfguid])
 AC_SUBST(
  [LIBFGUID_LIBADD],
  [../libfguid/libfguid.la])
 ac_cv_libfguid=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFGUID],
 [test "x$ac_cv_libfguid" = xlocal])

dnl Check for enabling libfwsi for Windows Shell identifier support
AC_CHECK_LIBFWSI

AS_IF(
 [test "x$ac_cv_libfwsi" = xyes],
 [AC_SUBST(
  [libesedb_pc_libs_private_libfwsi],
  [-lfwsi])
 ])

AS_IF(
 [test "x$ac_cv_libfwsi" = xyes],
 [AC_SUBST(
  [libesedb_spec_requires_libfwsi],
  [libfwsi])
 AC_SUBST(
  [libesedb_spec_build_requires_libfwsi],
  [libfwsi-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfwsi" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFWSI],
  [1],
  [Define to 1 if the local version of libfwsi is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFWSI],
  [1])
 AC_SUBST(
  [LIBFWSI_CPPFLAGS],
  [-I../libfwsi])
 AC_SUBST(
  [LIBFWSI_LIBADD],
  [../libfwsi/libfwsi.la])
 ac_cv_libfwsi=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFWSI],
 [test "x$ac_cv_libfwsi" = xlocal])

dnl Check if lnktools should be build as static executables
AS_IF(
 [test "x$ac_cv_enable_static_executables" != xno],
 [STATIC_LDFLAGS="-all-static";
 AC_SUBST(
  [STATIC_LDFLAGS])
 AC_DEFINE(
  [HAVE_STATIC_EXECUTABLES],
  [1],
  [Define if executables should be static compiled.])
 ac_cv_enable_static_executables=yes])

dnl Check if liblnk should be build with verbose output
AS_IF(
 [test "x$ac_cv_enable_verbose_output" != xno ],
 [AC_DEFINE(
  [HAVE_VERBOSE_OUTPUT],
  [1],
  [Define to 1 if verbose output should be used.])
 ac_cv_enable_verbose_output=yes])

dnl Check if liblnk should be build with debug output
AS_IF(
 [test "x$ac_cv_enable_debug_output" != xno ],
 [AC_DEFINE(
  [HAVE_DEBUG_OUTPUT],
  [1],
  [Define to 1 if debug output should be used.])
 ac_cv_enable_debug_output=yes])

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_liblnk_have_libuna" = xyes || test "x$ac_liblnk_have_libbfio" = xyes || test "x$ac_liblnk_have_libfdatetime" = xyes || test "x$ac_liblnk_have_libfguid" = xyes || test "x$ac_liblnk_have_libfwsi" = xyes],
 [AC_SUBST(
  [liblnk_spec_requires],
  [Requires:])
 AC_SUBST(
  [liblnk_spec_build_requires],
  [BuildRequires:]) ],
 [AC_SUBST(
  [liblnk_spec_requires],
  [])
 AC_SUBST(
  [liblnk_spec_build_requires],
  [])
 ac_liblnk_dummy=yes])

dnl Set memwatch support
ac_liblnk_have_memwatch=no

AS_IF(
 [test "x$ac_liblnk_have_memwatch" != xno ],
 [AC_SUBST(
  [MEMWATCH_CPPFLAGS],
  ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
  [MEMWATCH_LIBADD],
  [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_liblnk_have_memwatch" != xno])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Check if DLL support is needed in lnktools
AS_IF(
 [test x"$enable_shared" = xyes],
 [AS_CASE(
  [$host],
  [*cygwin* | *mingw*],
  [AC_SUBST(
   [LIBLNK_DLL_IMPORT],
   ["-DLIBLNK_DLL_IMPORT"])
  ])
 ])

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libnotify/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libbfio/Makefile])
AC_CONFIG_FILES([libfdatetime/Makefile])
AC_CONFIG_FILES([libfguid/Makefile])
AC_CONFIG_FILES([libfwsi/Makefile])
AC_CONFIG_FILES([liblnk/Makefile])
AC_CONFIG_FILES([libsystem/Makefile])
AC_CONFIG_FILES([lnktools/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([tests/Makefile])
AC_CONFIG_FILES([examples/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/liblnk.h])
AC_CONFIG_FILES([include/liblnk/definitions.h])
AC_CONFIG_FILES([include/liblnk/features.h])
AC_CONFIG_FILES([include/liblnk/types.h])
AC_CONFIG_FILES([liblnk/liblnk_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([liblnk.pc])
AC_CONFIG_FILES([liblnk.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Building:
   libuna support:                           $ac_cv_libuna
   libbfio support:                          $ac_cv_libbfio
   libfdatetime support:                     $ac_cv_libfdatetime
   libfguid support:                         $ac_cv_libfguid
   libfwsi support:                          $ac_cv_libfwsi

Features:
   Wide character type support:              $ac_cv_enable_wide_character_type
   lnktools are build as static executables: $ac_cv_enable_static_executables
   Verbose output:                           $ac_cv_enable_verbose_output
   Debug output:                             $ac_cv_enable_debug_output
]);


