#BHEADER***********************************************************************
# (c) 1998   The Regents of the University of California
#
# See the file COPYRIGHT_and_DISCLAIMER for a complete copyright
# notice, contact person, and disclaimer.
#
# $Revision: 1.2 $
#EHEADER***********************************************************************

SHELL = /bin/sh

srcdir = .

HYPRE_DIRS =\
 utilities\
 krylov\
 IJ_mv\
 parcsr_ls\
 parcsr_mv\
 seq_mv\
 struct_mv\
 sstruct_mv\
 test

all:
	@ \
	for i in ${HYPRE_DIRS}; \
	do \
	  if [ -d $$i ]; \
	  then \
	    echo "Making $$i ..."; \
	    (cd $$i; make); \
	    echo ""; \
	  fi; \
	done

clean:
	@ \
	for i in ${HYPRE_DIRS}; \
	do \
	  if [ -d $$i ]; \
	  then \
	    echo "Cleaning $$i ..."; \
	    (cd $$i; make clean); \
	  fi; \
	done

veryclean:
	@ \
	for i in ${HYPRE_DIRS}; \
	do \
	  if [ -d $$i ]; \
	  then \
	    echo "Very-cleaning $$i ..."; \
	    (cd $$i; make veryclean); \
	  fi; \
	done

tags:
	find . -name "*.c" -or -name "*.C" -or -name "*.h" -or -name "*.c??" -or -name "*.h??" -or -name "*.f" | etags -
