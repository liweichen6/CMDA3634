ALL: all

MAKE   = make --no-print-directory
SHELL  = /bin/bash
MKDIR  = mkdir
RM     = rm
CP     = cp

top_srcdir        = .
srcdir            = .

# Build directories
includebuild_dir  = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/include
libbuild_dir      = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/lib
binbuild_dir      = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/bin
sbinbuild_dir     = @sbinbuild_dir@

# Building Fortran to C interface
MPE_BUILD_FORTRAN2C  = no
# MPI implementation: used to turn on/off of certain feature
MPI_IMPL             = UserSupplied
# MPE header files that are needed by endusers
MPE_HEADERS          = mpe_misc.h

all: build_include
	$(MAKE) $(MAKEOPTS) build_lib_bin

#######  Building from the source
build_include:
	@-if [ -n "$(includebuild_dir)" ] ; then \
	      if [ ! -d $(includebuild_dir) ] ; then \
	          $(MKDIR) -p $(includebuild_dir) ; \
	      fi ; \
	      for file in $(MPE_HEADERS) ; do \
	          if [ -f $(top_srcdir)/include/$$file ] ; then \
	              $(CP) -f $(top_srcdir)/include/$$file \
	                       $(includebuild_dir) ; \
	          fi ; \
	      done ; \
	  fi

build_lib_bin:
	@( cd src && $(MAKE) $(MAKEOPTS) )

########  Linkage Tests
linktest_all: linktest_C linktest_F77

linktest_C:

linktest_F77:

########  Cleaning
# This is always a VPATH build, cleaning up the MPE_HEADERS
clean_include:
	@-cd $(includebuild_dir) && \
	  for file in $(MPE_HEADERS) ; do \
	      $(RM) -f $$file ; \
	  done

clean_lib:

clean_bin:

clean: clean_bin clean_lib
	@( cd src && $(MAKE) $(MAKEOPTS) clean )

distclean: clean_include clean_bin clean_lib
	@-( cd src && $(MAKE) $(MAKEOPTS) distclean )
	@-$(RM) -f mpe_misc_conf.h
	@-$(RM) -f Makefile
	@-$(RM) -f config.log config.status
	@-$(RM) -rf autom4te*.cache

maintainer-clean: distclean
	@-$(RM) -f mpe_misc_conf.h.in

owner-clean: maintainer-clean
	@-$(RM) -f configure
