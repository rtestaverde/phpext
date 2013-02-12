PHP_ARG_ENABLE(rtvhw, whether to enable RtvHW extension, [  --enable-rtvhw   Enable RtvHW extension])

if test "$PHP_RTVHW" != "no"; then

  PHP_NEW_EXTENSION(rtvhw, rtvhw.c rtvtemplate.c, $ext_shared)

  case $build_os in
  darwin1*.*.*)
    AC_MSG_CHECKING([whether to compile for recent osx architectures])
    CFLAGS="$CFLAGS -arch i386 -arch x86_64 -mmacosx-version-min=10.5"
    AC_MSG_RESULT([yes])
    ;;
  darwin*)
    AC_MSG_CHECKING([whether to compile for every osx architecture ever])
    CFLAGS="$CFLAGS -arch i386 -arch x86_64 -arch ppc -arch ppc64"
    AC_MSG_RESULT([yes])
    ;;
  esac
fi
