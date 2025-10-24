#Header.

MKDIR := mkdir -p
RM    := rm -rf
CP    := cp
MV    := mv

DESTDIR :=
PREFIX  := /usr/local
MNPATH  := /usr/local/man

CC := gcc
FC := gfortran

FLAGS    := -Wall -Wextra -pedantic -fopenmp
CFLAGS   := -MMD -std=gnu11
FFLAGS   := -std=f2018
LIBFLAGS := -fpic -shared

SRC  := src
SRCS := $(wildcard $(SRC)/*.c)
#We list the Fortran side sources in dependency order.
SRCS += $(SRC)/FC_Kinds.F90 $(SRC)/Prime_Factors.F90 $(SRC)/EINT_Core.F90 $(SRC)/EINT.F90

INCLUDE := inc

LDFLAGS :=
LDLIBS  :=

DEFINITIOS := # -D BUFFER_MIN_SIZE=10

#Required to build Fortran sources.
.NOTPARALLEL:

#Release profile.

BIN := bin
OBJ := obj

EXE := $(BIN)/eint
LIB := $(BIN)/libeint.so
HED := $(INCLUDE)/EINT.h

RELFLAGS := -Werror -O3 -DNDEBUG

COBJS := $(filter %.co, $(patsubst $(SRC)/%.c,$(OBJ)/%.co,$(SRCS)))
FOBJS := $(filter %.fo, $(patsubst $(SRC)/%.F90,$(OBJ)/%.fo,$(SRCS)))
OBJS  := $(COBJS) $(FOBJS)
FMODS := $(filter %.mod, $(patsubst $(SRC)/%.F90,$(OBJ)/%.mod,$(SRCS)))

CDEPS := $(filter %.cd, $(patsubst $(OBJ)/%.co,$(OBJ)/%.cd,$(OBJS)))
FDEPS := $(filter %.fd, $(patsubst $(OBJ)/%.fo,$(OBJ)/%.fd,$(OBJS)))
DEPS  := $(CDEPS) $(FDEPS)

#Debug profile.

DBGBIN := dbgbin
DBGOBJ := dbgobj

DBGEXE := $(DBGBIN)/eint
DBGLIB := $(DBGBIN)/libeint.so

DBGFLAGS := -g -O0 --coverage -DDBG_PRF

DBGCOBJS := $(filter %.co, $(patsubst $(SRC)/%.c,$(DBGOBJ)/%.co,$(SRCS)))
DBGFOBJS := $(filter %.fo, $(patsubst $(SRC)/%.F90,$(DBGOBJ)/%.fo,$(SRCS)))
DBGOBJS  := $(DBGCOBJS) $(DBGFOBJS)
DBGFMODS := $(filter %.mod, $(patsubst $(SRC)/%.F90,$(DBGOBJ)/%.mod,$(SRCS)))

DBGCDEPS := $(filter %.cd, $(patsubst $(DBGOBJ)/%.co,$(DBGOBJ)/%.cd,$(DBGOBJS)))
DBGFDEPS := $(filter %.fd, $(patsubst $(DBGOBJ)/%.fo,$(DBGOBJ)/%.fd,$(DBGOBJS)))
DBGDEPS  := $(DBGCDEPS) $(DBGFDEPS)

#Test profile.
TESTDIR  := test
TESTEXE  := $(TESTDIR)/Run_Tests.o
TESTSRC  := $(TESTDIR)/suites
TESTSRCS := $(wildcard $(TESTSRC)/*.c)
TESTOBJS := $(filter-out $(DBGOBJ)/main.co,$(DBGOBJS))

#Targets.

.PHONY: release debug test runtest install uninstall clean

release: $(EXE) $(LIB)

$(EXE): $(OBJS) | $(BIN)
		$(FC) $(FLAGS) $(FFLAGS) $(CFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $^ -o $@
		$(RM) *.mod

$(LIB): $(FOBJS) | $(BIN)
		$(FC) $(LIBFLAGS) $(FLAGS) $(FFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $(FOBJS) -o $@

$(OBJ)/%.co: $(SRC)/%.c | $(OBJ)
		$(CC) $(FLAGS) $(CFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(OBJ)/%.fo: $(SRC)/%.F90 | $(FMODS) $(OBJ)
		$(FC) $(FLAGS) $(FFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(OBJ)/%.mod: $(SRC)/%.F90 | $(OBJ)
		$(FC) $(FLAGS) $(FFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -fsyntax-only -J$(OBJ) $^

-include $(DEPS)

debug: $(DBGEXE) $(DBGLIB)

$(DBGEXE): $(DBGOBJS) | $(DBGBIN)
		$(FC) $(FLAGS) $(FFLAGS) $(CFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $^ -o $@
		$(RM) *.mod *.gcno

$(DBGLIB): $(DBGFOBJS) | $(DBGBIN)
		$(FC) $(LIBFLAGS) $(FLAGS) $(FFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $(DBGFOBJS) -o $@

$(DBGOBJ)/%.co: $(SRC)/%.c | $(DBGOBJ)
		$(CC) $(FLAGS) $(CFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(DBGOBJ)/%.fo: $(SRC)/%.F90 | $(DBGFMODS) $(DBGOBJ)
		$(FC) $(FLAGS) $(FFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(DBGOBJ)/%.mod: $(SRC)/%.F90 | $(DBGOBJ)
		$(FC) $(FLAGS) $(FFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -fsyntax-only -J$(DBGOBJ) $^

-include $(DBGDEPS)

$(BIN) $(OBJ) $(DBGBIN) $(DBGOBJ):
		$(MKDIR) $@

-include static_analysis

clean:
		$(RM) $(OBJ) $(BIN) $(DBGBIN) $(DBGOBJ)
		$(RM) $(TESTDIR)/*.gcda
		$(RM) $(TESTDIR)/*.gcno
		$(RM) $(TESTDIR)/*.d
		$(RM) $(TESTDIR)/*.o
		$(RM) $(TESTDIR)/coverage.info
		$(RM) $(TESTDIR)/report
		$(RM) $(TIDYDIR)

test: clean $(TESTEXE) runtest

$(TESTEXE): $(TESTOBJS) $(TESTSRCS) $(TESTDIR)/Driver.c | $(DBGBIN)
		$(FC) $(FLAGS) $(CFLAGS) $(DBGFLAGS) -I$(INCLUDE) -I$(TESTSRC) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $(TESTOBJS) $(TESTDIR)/Driver.c -o $@
		$(RM) *.mod

runtest: $(TESTEXE)
		./test/Test_Link_to_Binary.sh
		./$(TESTEXE) 1> /dev/null
		valgrind --leak-check=full ./$(TESTEXE) > tmpp.log 2>&1
		export OMP_NUM_THREADS=1
		valgrind --leak-check=full ./$(TESTEXE) > tmps.log 2>&1
		$(RM) $(TESTDIR)/*.gcda
		$(RM) $(TESTDIR)/*.gcno
		$(RM) *.gcno
		$(CP) $(DBGOBJ)/*.gcda $(TESTDIR)
		$(CP) $(DBGOBJ)/*.gcno $(TESTDIR)
		lcov --capture --directory $(TESTDIR) --output-file=$(TESTDIR)/coverage.info > /dev/null 2>&1
		genhtml $(TESTDIR)/coverage.info --output-directory=$(TESTDIR)/report > /dev/null 2>&1
		$(MV) tmpp.log $(TESTDIR)/report/valgrind_p_run.log
		$(MV) tmps.log $(TESTDIR)/report/valgrind_s_run.log

install: release
		install -d $(DESTDIR)$(PREFIX)/bin/
		install -m 755 $(EXE) $(DESTDIR)$(PREFIX)/bin/
		install -d $(DESTDIR)$(PREFIX)/lib/
		install -m 644 $(LIB) $(DESTDIR)$(PREFIX)/lib/
		install -d $(DESTDIR)$(PREFIX)/include/
		install -m 644 $(HED) $(DESTDIR)$(PREFIX)/include/
		gzip < ManPage > eint.1.gz
		install -d $(DESTDIR)$(MNPATH)/man1
		install -m 644 eint.1.gz $(DESTDIR)$(MNPATH)/man1
		$(RM) eint.1.gz

uninstall:
		$(RM) $(DESTDIR)$(PREFIX)/bin/eint
		$(RM) $(DESTDIR)$(PREFIX)/lib/libeint.so
		$(RM) $(DESTDIR)$(PREFIX)/include/EINT.h
		$(RM) $(DESTDIR)$(MNPATH)/man1/eint.1.gz
