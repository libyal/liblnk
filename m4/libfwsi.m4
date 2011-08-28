dnl Functions for libfwsi

dnl Function to detect if libfwsi is available
AC_DEFUN([AC_CHECK_LIBFWSI],
 [dnl Check if parameters were provided
 AS_IF(
  [test x"$ac_cv_with_libfwsi" != x && test "x$ac_cv_with_libfwsi" != xno && test "x$ac_cv_with_libfwsi" != xauto-detect],
  [AS_IF(
   [test -d "$ac_cv_with_libfwsi"],
   [CFLAGS="$CFLAGS -I${ac_cv_with_libfwsi}/include"
   LDFLAGS="$LDFLAGS -L${ac_cv_with_libfwsi}/lib"],
   [AC_MSG_WARN([no such directory: $ac_cv_with_libfwsi])
   ])
  ])

 AS_IF(
  [test x"$ac_cv_with_libfwsi" != xno],
  [dnl Check for headers
  AC_CHECK_HEADERS([libfwsi.h])
 
  AS_IF(
   [test "x$ac_cv_header_libfwsi_h" = xno],
   [ac_cv_libfwsi=no],
   [ac_cv_libfwsi=yes
   AC_CHECK_LIB(
    fdatetime,
    libfwsi_get_version,
    [],
    [ac_cv_libfwsi=no])
  
   dnl TODO add functions
   ])
  ])

 AS_IF(
  [test "x$ac_cv_libfwsi" = xyes],
  [AC_SUBST(
   [HAVE_LIBFWSI],
   [1]) ],
  [AC_SUBST(
   [HAVE_LIBFWSI],
   [0])
  ])
 ])

