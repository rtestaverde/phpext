#ifndef RTVTEMPLATE_H
#define RTVTEMPLATE_H

void rtv_init_rtvtemplate(TSRMLS_D);

PHP_METHOD(RtvTemplate,render);
PHP_METHOD(RtvTemplate,__construct);
PHP_METHOD(RtvTemplate,getInstance);

#endif
