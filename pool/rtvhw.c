#include <php.h>
#include "rtvhw.h"
#include "rtvtemplate.h"

zend_function_entry rtvhw_functions[] = {
  PHP_FE(rtvcopy, NULL)
  PHP_FE(rtvwelcome,NULL)
  { NULL, NULL, NULL }
};

zend_module_entry rtvhw_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_RTVHW_EXTNAME,
  rtvhw_functions,
  PHP_MINIT(rtvhw),
  NULL,
  NULL,
  NULL,
  NULL,
  PHP_RTVHW_VERSION,
  STANDARD_MODULE_PROPERTIES
};

PHP_MINIT_FUNCTION(rtvhw) {
  rtvhw_init_rtvtemplate(TSRMLS_C);
}

ZEND_GET_MODULE(rtvhw)

PHP_FUNCTION(rtvcopy) {
    php_printf("<author>&copy;2013 Roberto Testaverde</author>\n");
};

PHP_FUNCTION(rtvwelcome){
   	zend_bool english=0;
   	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &english) == FAILURE){
		return;
	}
	if(english){
		php_printf("<h1>Welcome</h1>");
	} else{
		php_printf("<h1>Benventuto</h1>");
	}
};
