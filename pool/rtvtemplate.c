#include <php.h>
#include <zend.h>
#include <zend_API.h>

#include "rtvhw.h"
#include "rtvtemplate.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_construct,0,0,0)
	ZEND_ARG_INFO(0,name)
	ZEND_ARG_INFO(0,healt)
	ZEND_ARG_INFO(0,sanity)
ZEND_END_ARG_INFO()

zend_class_entry *rtv_ce_rtvtemplate;

static function_entry rtvtemplate_methods[] = {
	PHP_ME(RtvTemplate,__construct, arginfo_construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(RtvTemplate,getInstance, arginfo_construct, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(RtvTemplate, render, NULL, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void rtv_init_rtvtemplate(TSRMLS_D){
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce,"RtvTemplate",rtvtemplate_methods);
	rtv_ce_rtvtemplate = zend_register_internal_class(&ce TSRMLS_CC);

	/* fields */
	zend_declare_property_bool(rtv_ce_rtvtemplate,"html", strlen("html"),1,ZEND_ACC_PUBLIC TSRMLS_CC);
}

PHP_METHOD(RtvTemplate, __construct){
	char *name = "v";
	int name_len = sizeof("v")-1;

	long healt = 10, sanity = 4;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll",&name,&name_len,&healt,&sanity)==FAILURE){
		return;
	}

	zend_update_property_stringl(rtv_ce_rtvtemplate,getThis(),"name",strlen("name"),name, name_len TSRMLS_CC);
	zend_update_property_long(rtv_ce_rtvtemplate,getThis(),"healt",strlen("healt"),healt TSRMLS_CC);
	zend_update_property_long(rtv_ce_rtvtemplate,getThis(), "sanity", strlen("sanity"),sanity TSRMLS_CC);
}

PHP_METHOD(RtvTemplate, getInstance){
	char *name="default name";
	int name_len= sizeof("default name"-1);
	long healt=22, sanity=22;
	object_init_ex(return_value,rtv_ce_rtvtemplate);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll",&name,&name_len,&healt,&sanity)==FAILURE){
                return;
        }
	add_property_stringl(return_value, "name", name, name_len, 1);
	add_property_long(return_value,"healt",healt);
	add_property_long(return_value,"sanity",sanity);
}

PHP_METHOD(RtvTemplate, render){
	char *test="testo di default";
	int test_len = sizeof("testo di default")-1;
	 if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|sll",&test,&test_len)==FAILURE){
                return;
        }

	php_printf("<h1>");
	php_printf(test);
	php_printf("</h1>");
}
