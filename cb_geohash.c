/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_cb_geohash.h"
#include "./geohash.h"

/* If you declare any globals in php_cb_geohash.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(cb_geohash)
*/

/* True global resources - no need for thread safety here */
static int le_cb_geohash;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("cb_geohash.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_cb_geohash_globals, cb_geohash_globals)
    STD_PHP_INI_ENTRY("cb_geohash.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_cb_geohash_globals, cb_geohash_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_cb_geohash_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cb_geohash_encode)
{
	double lon, lat;
	int precision = 12;

	array_init(return_value);

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd|l", &lon, &lat, &precision) == FAILURE) {
		return;
	}

    char *binary, *str;
    binary = lon_lat_to_binary(lon, lat, precision);
	str = base32_encode(binary);

	RETURN_STRING(str);
}

PHP_FUNCTION(cb_geohash_decode)
{
	char  *geo_str;
	size_t str_length;

	array_init(return_value);

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &geo_str, &str_length) == FAILURE) {
		return;
	}

    double *p = char_to_binary(geo_str, str_length);
	add_assoc_double(return_value, "lon", p[0]);
	add_assoc_double(return_value, "lat", p[1]);

}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_cb_geohash_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_cb_geohash_init_globals(zend_cb_geohash_globals *cb_geohash_globals)
{
	cb_geohash_globals->global_value = 0;
	cb_geohash_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cb_geohash)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(cb_geohash)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cb_geohash)
{
#if defined(COMPILE_DL_CB_GEOHASH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(cb_geohash)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cb_geohash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cb_geohash support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ cb_geohash_functions[]
 *
 * Every user visible function must have an entry in cb_geohash_functions[].
 */
const zend_function_entry cb_geohash_functions[] = {
	PHP_FE(cb_geohash_encode, NULL)
	PHP_FE(cb_geohash_decode, NULL)
	PHP_FE_END	/* Must be the last line in cb_geohash_functions[] */
};
/* }}} */

/* {{{ cb_geohash_module_entry
 */
zend_module_entry cb_geohash_module_entry = {
	STANDARD_MODULE_HEADER,
	"cb_geohash",
	cb_geohash_functions,
	PHP_MINIT(cb_geohash),
	PHP_MSHUTDOWN(cb_geohash),
	PHP_RINIT(cb_geohash),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(cb_geohash),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(cb_geohash),
	PHP_CB_GEOHASH_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CB_GEOHASH
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(cb_geohash)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
