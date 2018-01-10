# The nchdf4 Library  
__Summary__: The nchdf4 library has one purpose: to serve as the HDF4 library  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
when the netcdf-c library is built with HDF4 support.  
## Table of Contents
* [Introduction](#Introduction)  
* [Dependencies](#Dependencies)
* [Download](#Download)
* [Automake Build](#Automake)
* [Cmake Build for Linux](#Cmake)
* [Miscellaneous Notes](#Misc)
* [References](#References)  
* [Contact Information](#Contact)

## <a name="Introduction">Introduction</a>

The nchdf4 library has one purpose: to serve as the HDF4 library
to use with netcdf-c when the netcdf-c library is built with
the "--enable-hdf4" flag is specified to the configure command.

The nchdf4 library is a stripped version of the
original HDF4 library [1]. The version number of nchdf4
is the same as the base HDF4 library version from which it
is derived.

To this end, the original HDF4 library was stripped of all its
code that attempts to provide netcdf functionality.  Obviously,
this effort was a pure hack, and there is still a lot of cruft
and duplication in the code and the configuration files.  The
biggest problem is that much of the code is conditional'd on
specific machines (e.g. hpux or ia64) rather than on specific
properties (e.g. is the machine big-endian, is long 32 bit or 64
bit).

The current successful build matrix is as follows.
<table>
<tr><th>OS<th>Word Size<th>C Compiler<th>Autoconf<th>Cmake
<tr><td>Linux(Centos7)<td>64-bit<td>gcc 6.4.0<td>yes<td>yes
<tr><td>Cygwin<td>32-bit<td>gcc 6.4.0<td>yes<td>no
<tr><td>Visual Studio<br>Community Edition<td>14.0<td>64-bit<td>no<td>yes
</table>

<!-- Visual Studio version 14 2015 (Community Edition) -->

It is probable that it can be made to work for other platforms
with modest effort.

## <a name="Dependencies">Dependencies</a>

The HDF4 code depends on two required and one optional libraries.
* libz (see [2])
* jpeg (see [3])
* (optional) szip (see [4])

For the remainder of this document, we will assume these libraries
are located in /usr/local/lib. Your location may vary.

## <a name="Download">Download</a>

The simplest way is to download the source from github here:
    https://github.com/DennisHeimbigner/nchdf4.git

## <a name="Automake">Automake Build</a>

1. Create the ./configure program by executing this command.
````
    autoreconf -i --force
````

2. Specify the location of the required libraries.
````
	export LDFLAGS="-L/usr/local/lib -lz -ljpeg"
````
if the optional szip library is available, then one can 
add "-lsz" to the above command.

3. Optionally set the compiler optimizations.
````
	export CFLAGS="-g -O0"
````

4. Configure the build by executing the configure command.  The
following command, for example, will build a static and dynamic
version by default and install it in the directories under
"/usr/local" (bin, lib, include).  If szip support is desired,
then add the option "--enable-szip" to the ./configure command.
````
	./configure --prefix=/usr/local
````

5. Build the library(s)
````
	make all
````

6. Test the library(s)
````
	make check
````

7. Install the library in the location specied as the prefix in the
above ./configure command. This command may need to be executed
as root or using the sudo command.
````
	make install
````

## <a name="Cmake">Cmake Build for Linux</a>

1. Specify the location of the required libraries.
````
	export LDFLAGS="-L/usr/local/lib -lz -ljpeg"
````
if the optional szip library is available, then one can 
add "-lsz" to the above command.

2. Create a directory for the cmake build
````
	mkdir ./build
````

3. Enter the build directory and configure the build by invoking cmake with a number of flags.
````
	cd ./build
	cmake -DCMAKE_INSTALL_PREFIX=`/usr/local" 
````
If the optional szip library is available, then one can 
add "-DENABLE_SZIP" to the above command.

The flag "-DCMAKE_INSTALL_PREFIX" specifies where to install
the libraries and headers and executables.

4. Build the library(s) (while still in the build directory)
````
	make all
````

6. Test the library(s) (while still in the build directory)
````
	make test
````

7. Install the library in the location specied as the prefix in the
above ./configure command. This command may need to be executed
as root or using the sudo command.
````
	make install
````
## <a name="Misc">Miscellaneous Notes</a>

1. There is still substantial cruft that could be removed.
2. The github repository contains some files solely for author's use: e.g. cf, cf.cmake.
3. nchdf4 has its own copy of netcdf-h, which may need to be updated if
   any relevant constants change.

## <a name="References">References</a>
[1] https://support.hdfgroup.org/release4/obtainsrc.html#src  
[2] Source for libz: https://support.hdfgroup.org/release4/obtain.html#extlibs  
[3] Source for libjpeg: https://support.hdfgroup.org/release4/obtain.html#extlibs  
[4] Source for Libsz: https://gitlab.dkrz.de/k202009/libaec.git  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Libaec can also process szip. This is open source and license free. Hence it  preferable to the one on libz/libjpeg page.

## <a name="Contact">Contact Information</a>
__Author__: Dennis Heimbigner, Unidata  
__Initial Draft__: 2017-12-1  
__Last Revised__: 2017-12-20  
__Current HDF4 Version__: 4.2.13  
__Support__: mailto:support-netcdf@unidata.ucar.edu

