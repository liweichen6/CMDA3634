
##### User configurable options #####

MPI_CC      = /usr/bin/mpicc
MPI_CLINKER = $(MPI_CC)
#
MPI_CFLAGS  = -I/usr/lib/openmpi/include 
MPI_LIBS    = -L/usr/lib/openmpi/lib -lmpi
CFLAGS      = 
MPE_INCDIR  = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/include
MPE_LIBDIR  = /home/liw/CMDA3634/Lecture/L10e/mpe2-2.4.9b/lib
PROF_LIBS   = -L$(MPE_LIBDIR) -lmpe -lX11 $(MPI_LIBS) -lm
#
INCLUDE_DIR = -I$(MPE_INCDIR)
LDFLAGS     = 

### End User configurable options ###

RM          = rm

VPATH=.:$(srcdir)

srcdir      = .

# MPE include path, x_INCS, goes in front of MPI include path, MPI_xFLAGS,
# in case MPI include path is in MPI_xFLAGS containing old MPE include path.
MPICC_FLAGS   = $(INCLUDE_DIR) $(MPI_CFLAGS) $(MPE_COPTS)
MPICC_LDFLAGS = $(LDFLAGS) $(MPI_CFLAGS) $(MPE_LDOPTS)
EXECS         = life_g

.SUFFIXES: .c .o 

.c.o:
	$(MPI_CC) $(MPICC_FLAGS) -c $<

default: $(EXECS)

life_g:	life_g.o
	$(MPI_CLINKER) $(MPICC_LDFLAGS) -o $@ $? $(PROF_LIBS)

clean:
	@-$(RM) -f *.o *~ PI* $(EXECS)

distclean: clean
	@-$(RM) -f Makefile
