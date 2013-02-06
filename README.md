Case study for a php extension 
===
1. compiling a version of PHP to enabling debug support 
2. configuring Apache to work whith different versions of PHP 
3. compiling first php extension 


1. Compilign a version of PHP to enabling debug support 
---
The very first step is to obtain a **debuggable** working copy of PHP. 
So the target of this thread is to leave different versions of PHP working togheter (and whithout conflicts) 
on the same (linux) machine. 
Notes for environment:

- Linux ubuntu32 3.2.0-26-generic-pae i386 (virtualbox)
- PHP used in this development 5.3.21
- Apache/2.2.22 (Ubuntu) Feb 13 2012 01:37:27

Make a directory and move to it (wherever you want)
```bash
	$ mkdir php53 && cd php53 Download a PHP source package
	$ wget http://www.php.net/get/php-5.3.21.tar.gz/from/es2.php.net/mirror
```
Untar [and delete source package] and move to it
```bash
	$ tar -xvf php-5.3.21.tar.gz
	[$ rm php-5.3.21.tar.gz]
	$ cd php-5.3.21/ 
```
Create a directory to compile the source
```bash
	$ mkdir debug-zts 
```
Create an environment variable to handle the development only for this shell session (leaving eventually others 
installations free of make their's job)
```bash
	$ PHPDEV=$(pwd); 
```
Run the configure command whith the options to enable the debug support, whith optionally other ones to compile extensions, and run install (if no errors)
```bash
	$ ./configure --enable-debug --enable-maintainer-zts --prefix=$PHPDEV/debug-zts [ more options ]
	$ make
	$ make install
```
Now you have the php5.3.21 installed in the $PHPDEV/debug-zts directory, and the executable in $PHPDEV/debug-zts/bin 
directory. Now save the executable path into a file to easy reload it and, very important, add this to your PATH
```bash
	$ echo $PHPDEV/debug-zts/bin>phpdev
	$ PATH=$(cat phpdev):$PATH
```
Next time you need to start development session use the last command to restore the PATH.
Test your PHP installation
```bash
	$ php -v
	PHP 5.3.21 (cli) (built: Feb 5 2013 12:58:28) (DEBUG)
	Copyright (c) 1997-2013 The PHP Group
	Zend Engine v2.3.0, Copyright (c) 1998-2013 Zend Technologies 
```
2. Configuring Apache to work whith different versions of PHP 
---
The easiest way is to configure various virtualhosts to use different PHP environment. To mantain a consistent environment, I use the same directory of the download in this example php53, so add a directory to store the virtualhost
```bash
	$ cd ~/php53 && mkdir www && cd www
	$ mkdir html && mkdir logs
```
The html directory will be your root dir, and the logs your error and access logs dir. Create a file in the www dir called php.conf whith this content [replacing the paths as in your installation]
```apache
	ScriptAlias /cgi-bin-php/ "[YOUR_PATH]/php53/php-5.3.21/debug-zts/bin/"
	SetEnv PHP_INI_SCAN_DIR "[YOUR_PATH]/php53/www/"
	AddHandler php-script .php
	Action php-script /cgi-bin-php/php-cgi
	<FilesMatch "\.php">
		SetHandler php-script
	</FilesMatch>
```
In this file you say to Apache where is the PHP executable you want to load, and where will found the php.ini 
file for this virtualhost. 
Create a virtualhost, you need root priviledges. First create the file in /etc/apache2/sites-available eg php53debug, 
changing the paths as into your installation

```apache
	<VirtualHost *:80>
		ServerAdmin [your@email.ltd]
		ServerName php53debug.ubuntu
		ServerAlias www.php53debug.ubuntu
		DocumentRoot [YOUR_PATH]/php53/www/html
		Include [YOUR_PATH]/php53/www/php.conf
		ErrorLog "[YOUR_PATH]/php53/www/logs/php53debug.error.log"
		CustomLog "[YOUR_PATH]/php53/www/logs/php53debug.access.log" common
		<Directory />
			Options FollowSymLinks
			AllowOverride All
		</Directory>
		<Directory [YOUR_PATH]/php53/www/html>
			Options Indexes FollowSymLinks MultiViews
			AllowOverride All
			Order allow,deny
			allow from all
		</Directory>
	</VirtualHost>
```

Feel free to change this settings at your will, the only important thing is the inclusion of the php.conf file. Enable the virtualhost and restart Apache
```bash
	$ sudo a2ensite php53debug
	$ sudo service apache2 restart 
```
Create a php.ini file (from scratch or copying an existing one) in the ~/php53/www/ directory (or wherever you point the PHO_INI_SCAN_DIR in the php.conf file.

At this time I need only the date.timezone parameter to be configured, so I create a php.ini file whith only a line

```ini
	date.timezone [YOUR_TIMEZONE eg Europe/Madrid]
```

Create a file in html dir whith the phpinfo() statement:

```php
	<?php
		phpinfo();
```
	
At this point calling your virtualhost/info.php from a browser will show the php configuration for this installation whithout conficts whith other eventual PHP instances.

3. Compiling first php extension 
---

This repository is organized in branches to get a step by step tutorial. First of all verify your path points to the correct PHP version, you need to do this step every time you start a development session to ensure whith which version are you working. It's very important don't forget it.
```bash
	$ cd ~/php53
	$ echo $PATH eventually
	$ PATH=$(phpdev):$PATH 
```
Create a directory in which make your development
```bash
	$ mkdir pool && cd pool Download the branch you wish to work on
	$ git checkout git://github.com/rtestaverde/phpext.git 
```
Create a directory for the compilation
```bash
	$ mkdir dev [modify and] copy the files into the dev directory
	$ cp ./*.* dev/
	$ cd dev/ 
```
Run the phpize command to create the structure of the headers and files you need to compile your extension, in my environment I have phpize5, so I'll use it:
```bash
	$ phpize5
	Configuring for:
	PHP Api Version: 20090626
	Zend Module Api No: 20090626
	Zend Extension Api No: 220090626
	$ ls
	acinclude.m4 autom4te.cache config.guess configure install-sh Makefile.global mkinstalldirs aclocal.m4 build config.h.in
	config.sub configure.in ltmain.sh missing run-tests.php [the extensions source files] 
```
Run compile and make and make install
```bash
	$ ./compile
	[...various output...]
	$ make
	[...various output...]
	----------------------------------------------------------------------
	Libraries have been installed in:
   		[YOUR_PATH]/php53/pool/dev/modules
   	If you ever happen to want to link against installed libraries in a given directory, 
   	LIBDIR, you must either use libtool, andspecify the full pathname of the library, or 
   	use the '-LLIBDIR' flag during linking and do at least one of the following:
		- add LIBDIR to the 'LD_LIBRARY_PATH' environment variable during execution
		- add LIBDIR to the 'LD_RUN_PATH' environment variable during linking
		- use the '-Wl,-rpath -Wl,LIBDIR' linker flag
		- have your system administrator add LIBDIR to '/etc/ld.so.conf'
	See any operating system documentation about shared libraries for more information,
	such as the ld(1) and ld.so(8) manual pages.
	----------------------------------------------------------------------
	
	Build complete.
	Don't forget to run 'make test'.
	
	$ make install 
	Installing shared extensions:     [YOUR_PATH]/php53/php-5.3.21/debug-zts/lib/php/extensions/debug-zts-20090626/

```

The extension is build and copied in your extension dir (it will put where). 
Enable the extesion in your php.ini file. Finally call the info.php whith the browser to see your installed and working extension.
