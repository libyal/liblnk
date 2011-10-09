dnl Function to detect if liblnk dependencies are available
AC_DEFUN([AX_LIBLNK_CHECK_LOCAL],
 [dnl Check for internationalization functions in liblnk/liblnk_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

