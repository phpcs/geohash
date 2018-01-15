dnl $Id$
dnl config.m4 for extension cb_geohash

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

 PHP_ARG_WITH(cb_geohash, for cb_geohash support,
 Make sure that the comment is aligned:
 [  --with-cb_geohash             Include cb_geohash support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(cb_geohash, whether to enable cb_geohash support,
dnl Make sure that the comment is aligned:
dnl [  --enable-cb_geohash           Enable cb_geohash support])

if test "$PHP_CB_GEOHASH" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-cb_geohash -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cb_geohash.h"  # you most likely want to change this
  dnl if test -r $PHP_CB_GEOHASH/$SEARCH_FOR; then # path given as parameter
  dnl   CB_GEOHASH_DIR=$PHP_CB_GEOHASH
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cb_geohash files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CB_GEOHASH_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CB_GEOHASH_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cb_geohash distribution])
  dnl fi

  dnl # --with-cb_geohash -> add include path
  dnl PHP_ADD_INCLUDE($CB_GEOHASH_DIR/include)

  dnl # --with-cb_geohash -> check for lib and symbol presence
  dnl LIBNAME=cb_geohash # you may want to change this
  dnl LIBSYMBOL=cb_geohash # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CB_GEOHASH_DIR/$PHP_LIBDIR, CB_GEOHASH_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CB_GEOHASHLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cb_geohash lib version or lib not found])
  dnl ],[
  dnl   -L$CB_GEOHASH_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CB_GEOHASH_SHARED_LIBADD)

  PHP_NEW_EXTENSION(cb_geohash, cb_geohash.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
