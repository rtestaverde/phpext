#ifndef RTVTEMPLATE_H
#define RTVTEMPLATE_H

typedef struct _rtv_template_fragments{
	zend_object std;
	int position;
	char *code;
} rtv_template_fragments;

zend_object_value create_rtv_template_fragments(zend_class_entry *class_type TSRMLS_DC);
void free_rtv_template_fragments(void *object TSRMLS_DC);

void rtv_init_rtvtemplate(TSRMLS_D);


PHP_METHOD(RtvTemplate,__construct);
PHP_METHOD(RtvTemplate,getInstance);
PHP_METHOD(RtvTemplate,render);
PHP_METHOD(RtvTemplate,getFragment);
#endif
