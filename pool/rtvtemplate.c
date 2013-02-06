#include <php.h>
#include "rtvtemplate.h"

zend_class_entry *rtv_ce_rtvtemplate;

static function_entry rtvtemplate_methods[] = {
	PHP_ME(RtvTemplate, render, NULL, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void rtvhw_init_rtvtemplate(TSRMLS_D){ 
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce,"RtvTemplate",rtvtemplate_methods);
	rtv_ce_rtvtemplate = zend_register_internal_class(&ce TSRMLS_CC);

	/* fields */
	zend_declare_property_bool(rtv_ce_rtvtemplate,"html", strlen("html"),1,ZEND_ACC_PUBLIC TSRMLS_CC);
}

PHP_METHOD(RtvTemplate, render){

}