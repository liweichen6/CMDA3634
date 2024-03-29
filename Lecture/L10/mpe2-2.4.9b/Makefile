ALL: all

MAKE   = make --no-print-directory
SHELL  = /bin/bash
MKDIR  = mkdir
RM     = rm
CP     = cp

top_srcdir        = .
srcdir            = .

VPATH = .:.

# Build directories
includebuild_dir  = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/include
libbuild_dir      = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/lib
binbuild_dir      = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/bin
sbinbuild_dir     = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/sbin
etcbuild_dir      = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/etc

# Building Fortran to C interface
MPE_BUILD_FORTRAN2C  = no
# MPI implementation: used to turn on/off of certain feature
MPI_IMPL             = UserSupplied
# MPE header files that are needed by endusers
MPE_HEADERS          = mpe.h mpe_misc.h mpe_callstack.h mpe_log.h mpe_graphics.h

# The empty string, "", in PKGS is needed to avoid /bin/sh from complaining
# when PKGS is really empty.
PKGS = ""  src/misc src/callstack src/logging src/wrappers src/graphics src/collchk src/slog2sdk

all-redirect: 
all: build_include
	$(MAKE) $(MAKEOPTS) build_lib_bin

#######  Building from the source
build_include:
	-@if [ -n "$(includebuild_dir)" ] ; then \
	      if [ ! -d $(includebuild_dir) ] ; then \
	          $(MKDIR) -p $(includebuild_dir) ; \
	      fi ; \
	      cd $(top_srcdir)/include && \
	      for file in $(MPE_HEADERS) ; do \
	          if [ ! -f $(includebuild_dir)/$$file ] ; then \
	              if [ -f $$file ] ; then \
	                  $(CP) $$file $(includebuild_dir) ; \
	              else \
	                  echo "/* This empty MPE header will be replaced by the correct header if the corresponding subpackage is configured successfully. */" > $(includebuild_dir)/$$file ; \
	              fi ; \
	          fi ; \
	      done ; \
	  fi

build_lib_bin:
	@for pkg in $(PKGS) ; do \
	     if [ -n "$$pkg" -a -s $$pkg/Makefile ] ; then \
	         echo ; echo "**** Making $$pkg ...." ; \
	         ( cd $$pkg && $(MAKE) $(MAKEOPTS) ) ; \
                 sleep 1 ; \
	     fi ; \
	 done

build_check:
	@if [ -n "$(MPERUN)" ] ; then \
	     ./sbin/mpecheckbuild -run="$(MPERUN)" ; \
	 else \
	     ./sbin/mpecheckbuild -run ; \
	 fi ; \

check : build_check

FORCE_TARGET:

########  Installing
install: FORCE_TARGET
	@installopts="-dmode=" ; \
	 if [ -n "$(PACKAGE)" ] ; then \
	     installopts="-package=$(PACKAGE) $$installopts" ; \
	 fi ; \
	 if [ -n "$(PREFIX)" ] ; then \
	     installopts="-prefix=$(PREFIX) $$installopts" ; \
	 fi ; \
	 if [ -n "$(prefix)" ] ; then \
	     installopts="-prefix=$(prefix) $$installopts" ; \
	 fi ; \
	 env DESTDIR=$(DESTDIR) ./sbin/mpeinstall $$installopts

installcheck:
	@installopts="" ; \
	 if [ -n "$(PACKAGE)" ] ; then \
	     installopts="-package=$(PACKAGE) $$installopts" ; \
	 fi ; \
	 if [ -n "$(PREFIX)" ] ; then \
	     installopts="-prefix=$(PREFIX) $$installopts" ; \
	 fi ; \
	 if [ -n "$(prefix)" ] ; then \
	     installopts="-prefix=$(prefix) $$installopts" ; \
	 fi ; \
	 env DESTDIR=$(DESTDIR) ./sbin/mpecheckinstall $$installopts

installcheck-all:
	@installopts="" ; \
	 if [ -n "$(MPERUN)" ] ; then \
	     installopts="-run=$(MPERUN) $$installopts" ; \
	 else \
	     installopts="-run $$installopts" ; \
	 fi ; \
	 if [ -n "$(PACKAGE)" ] ; then \
	     installopts="-package=$(PACKAGE) $$installopts" ; \
	 fi ; \
	 if [ -n "$(PREFIX)" ] ; then \
	     installopts="-prefix=$(PREFIX) $$installopts" ; \
	 fi ; \
	 if [ -n "$(prefix)" ] ; then \
	     installopts="-prefix=$(prefix) $$installopts" ; \
	 fi ; \
	 env DESTDIR=$(DESTDIR) ./sbin/mpecheckinstall $$installopts

uninstall:
	@env DESTDIR=$(DESTDIR) ./sbin/mpeuninstall

##### standard automake targets that may be invoked by MPICH2's make

# for now we just crudely copy everything from the source directory to the
# distdir given to us by the upper level makefile
distdir:
	cp -a $(srcdir)/* $(distdir)/

########  Cleaning
# when "$(top_srcdir)" = ".", it is a non-VPATH build.
clean_include:
	@-if [ -n "$(includebuild_dir)" -a "$(top_srcdir)" != "." \
	       -a "$(includebuild_dir)" != "$(top_srcdir)/include" ] ; then \
	      for file in $(MPE_HEADERS) ; do \
	          $(RM) -f $(includebuild_dir)/$$file ; \
	      done ; \
	  fi

clean_bin:
	@-for file in $(binbuild_dir)/* ; do \
	      case "$$file" in \
	          *.in) ;; \
	          *) $(RM) -f $$file ;; \
	      esac ; \
	  done

clean_lib:
	 -$(RM) -f $(libbuild_dir)/lib*
	 -$(RM) -f $(libbuild_dir)/*.jar
	 -$(RM) -f $(libbuild_dir)/*.o

clean_etc:
	 -$(RM) -f $(etcbuild_dir)/*.conf

clean: clean_lib
	@-for pkg in $(PKGS) ; do \
	      if [ -n "$$pkg" -a -s $$pkg/Makefile ] ; then \
	          ( cd $$pkg && $(MAKE) $(MAKEOPTS) clean ) ; \
	      fi ; \
	  done
	@-$(RM) -f work.pc work.pcl

distclean-misc: clean_include clean_etc
	-$(RM) -f sbin/mpetestlink sbin/mpetestexec sbin/mpetestexeclog
	-$(RM) -f sbin/mpecheckinstall sbin/mpecheckbuild
	-$(RM) -f sbin/mpeinstall sbin/mpeuninstall
	-$(RM) -f Makefile
	-$(RM) -f mpe_conf.h
	-$(RM) -r f77tmpdir
	-$(RM) -f config.log config.status
	-$(RM) -rf autom4te*.cache

distclean: clean_bin clean_lib distclean-misc
	@-for pkg in $(PKGS) ; do \
	      if [ -n "$$pkg" -a -s $$pkg/Makefile ] ; then \
	          echo "making distclean in $$pkg" ; \
	          ( cd $$pkg && $(MAKE) $(MAKEOPTS) distclean ) ; \
	      fi ; \
	  done

maintainer-clean: clean_bin clean_lib distclean-misc
	@-for pkg in $(PKGS) ; do \
	      if [ -n "$$pkg" -a -s $$pkg/Makefile ] ; then \
	          echo "making maintainer-clean in $$pkg" ; \
	          ( cd $$pkg && $(MAKE) $(MAKEOPTS) maintainer-clean ) ; \
	      fi ; \
	  done
	@-$(RM) -f mpe_conf.h.in

owner-clean: clean_bin clean_lib distclean-misc
	@-for pkg in $(PKGS) ; do \
	      if [ -n "$$pkg" -a -s $$pkg/Makefile ] ; then \
	          ( cd $$pkg && $(MAKE) $(MAKEOPTS) owner-clean ) ; \
	      fi ; \
	  done
	@-$(RM) -f mpe_conf.h.in
	@-$(RM) -f configure

configure_deps = $(top_srcdir)/configure.ac \
	$(top_srcdir)/aclocal_core.m4 \
	$(top_srcdir)/aclocal_f77.m4 \
	$(top_srcdir)/aclocal_make.m4 \
	$(top_srcdir)/aclocal_mpi.m4 \
	$(top_srcdir)/aclocal.m4
$(top_srcdir)/configure: # $(configure_deps)
	(cd $(top_srcdir) && ./autogen.sh)

Makefile: $(top_srcdir)/configure $(top_srcdir)/Makefile.in config.status
	./config.status

# Allow dependencies target
dependencies:

# Allow a coverage target
coverage:

# Allow a tags target
tags: TAGS
TAGS:
ctags: tags


##
## A Maintainer's target: Create a distribution of this release
## The easy approach is to create the distribution copy from the
## source files in the working directory.  An option that is more
## robust is to create it from a particular commit in the repository
## TODO: Add support for things like DISTDIR
DISTDIRS = etc src include cross_spec sbin bin maint
DISTFILES = INSTALL INSTALL.cross Makefile.in README README.windows \
        COPYRIGHT \
	aclocal.m4 aclocal_core.m4 aclocal_f77.m4 aclocal_inttypes.m4 \
	aclocal_make.m4 aclocal_mpi.m4 autogen.sh fmpe.def mpe.def \
	mpe.vcproj mpewrap.vcproj configure.ac install-sh config.sub \
	config.guess
# The chmod -R -N * command removes extended permission information,
# which OSX seems to add at the drop of a hat.  If those extended
# permissions are not removed, the tar file will contain a "dot" file
# for almost every file (!).
# WARNING: To ensure a clean distribution file, this executes a "distclean"
# step, which will remove all of the generated files, including this Makefile.
# The sed on configure.ac changes the default for maintainer mode from on to
# off
dist: Makefile
	@$(MAKE) distclean
	@if [ ! -d tmp ] ; then mkdir tmp ; \
	else echo "Remove the tmp directory first"; exit 1; fi
	@if [ -d mpe2-2.4.9b ] ; then \
	echo "Remove the mpe2-2.4.9b directory first"; exit 1; fi
	@if [ -f mpe2-2.4.9b.tgz ] ; then \
		$(RM) -f mpe2-2.4.9b.tgz ; fi
	for dir in $(DISTDIRS) ; do cp -rp $(top_srcdir)/$$dir tmp/$$dir ; done
	for file in $(DISTFILES) ; do cp -p $(top_srcdir)/$$file tmp/$$file ; done
	sed -e 's%useMaintainerMode=yes%useMaintainerMode=no%g' \
		$(top_srcdir)/configure.ac > tmp/configure.ac
	(cd tmp && ./autogen.sh)
	(cd tmp && chmod -R -N *)
	(cd tmp && find . -name '.gitignore*' -print | xargs $(RM))
	mv tmp mpe2-2.4.9b
	tar zcf mpe2-2.4.9b.tgz mpe2-2.4.9b
	$(RM) -rf mpe2-2.4.9b

################################################################################
# unimplemented targets that MPICH2's automake may recursively invoke; see
# "Third-Party Makefiles" in the automake manual

EMPTY_AUTOMAKE_TARGETS = install-data install-exec install-dvi install-html \
                         install-info install-ps install-pdf installdirs    \
                         mostlyclean dvi pdf ps info html
.PHONY: $(EMPTY_AUTOMAKE_TARGETS)
$(EMPTY_AUTOMAKE_TARGETS):


