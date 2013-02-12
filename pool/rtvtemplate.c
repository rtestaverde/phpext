#include <php.h>

#include "rtvhw.h"
#include "rtvtemplate.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_construct,0,0,3)
	ZEND_ARG_INFO(0,name)
	ZEND_ARG_INFO(0,healt)
	ZEND_ARG_INFO(0,sanity)
ZEND_END_ARG_INFO()

zend_class_entry *rtv_ce_rtvtemplate;

static function_entry rtvtemplate_methods[] = {
	PHP_ME(RtvTemplate,__construct, arginfo_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(RtvTemplate, getInstance, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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

PHP_METHOD(RtvTemplate, __construct){
	char *name;
	int name_len;
	
	long healt = 10, sanity = 4;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll",&name,&name_len,&healt,&sanity)==FAILURE){
		return;
	}
	
	zend_update_property_stringl(rtv_ce_rtvtemplate,getThis(),"name",strlen("name"),name, name_len TSRMLS_CC);
	zend_update_property_long(rtv_ce_rtvtemplate,getThis(),"healt",strlen("healt"),healt TSRMLS_CC);
	zend_update_property_long(rtv_ce_rtvtemplate,getThis(), "sanity", strlen("sanity"),sanity TSRMLS_CC);
}

PHP_METHOD(RtvTemplate, getInstance){
	object_init_ex(return_value,rtv_ce_rtvtemplate);
	CALL_METHOD(RtvTemplate, __construct, return_value, return_value);
	//CALL_METHOD3(RtvTemplate, __construct, return_value, return_value,'alibaba',15,27);
}

PHP_METHOD(RtvTemplate, render){

}