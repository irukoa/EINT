#Header.

MKDIR := mkdir
RM    := rm -rf
CP    := cp

CC := gcc
FC := gfortran

CFLAGS   := -MMD -Wall -Wextra -pedantic -std=gnu23
FFLAGS   := -MMD -Wall -Wextra -pedantic -std=f2023
LIBFLAGS := -fpic -shared

SRC  := src
SRCS := $(wildcard $(SRC)/*.c)
SRCS += $(wildcard $(SRC)/*.F90)

INCLUDE := inc

LDFLAGS :=
LDLIBS  :=

DEFINITIOS := # -D BUFFER_MIN_COLSIZE=10 -D BUFFER_MIN_ROWSIZE=10

PREFIX := /usr/local

#Release profile.

BIN := bin
OBJ := obj

EXE := $(BIN)/eint
LIB := $(BIN)/libeint.so

RELFLAGS := -Werror -O3 -DNDEBUG

COBJS := $(filter %.co, $(patsubst $(SRC)/%.c,$(OBJ)/%.co,$(SRCS)))
FOBJS := $(filter %.fo, $(patsubst $(SRC)/%.F90,$(OBJ)/%.fo,$(SRCS)))
OBJS  := $(COBJS) $(FOBJS)

CDEPS := $(filter %.cd, $(patsubst $(OBJ)/%.co,$(OBJ)/%.cd,$(OBJS)))
FDEPS := $(filter %.fd, $(patsubst $(OBJ)/%.fo,$(OBJ)/%.fd,$(OBJS)))
DEPS  := $(CDEPS) $(FDEPS)

#Debug profile.

DBGBIN := dbgbin
DBGOBJ := dbgobj

DBGEXE := $(DBGBIN)/eint
DBGLIB := $(DBGBIN)/libeint.so

DBGFLAGS := -g -O0 -DDBG_PRF --coverage

DBGCOBJS := $(filter %.co, $(patsubst $(SRC)/%.c,$(DBGOBJ)/%.co,$(SRCS)))
DBGFOBJS := $(filter %.fo, $(patsubst $(SRC)/%.F90,$(DBGOBJ)/%.fo,$(SRCS)))
DBGOBJS  := $(DBGCOBJS) $(DBGFOBJS)

DBGCDEPS := $(filter %.cd, $(patsubst $(DBGOBJ)/%.co,$(DBGOBJ)/%.cd,$(DBGOBJS)))
DBGFDEPS := $(filter %.fd, $(patsubst $(DBGOBJ)/%.fo,$(DBGOBJ)/%.fd,$(DBGOBJS)))
DBGDEPS  := $(DBGCDEPS) $(DBGFDEPS)

#Targets.

.PHONY: release debug clean

release: $(EXE) $(LIB)

$(EXE): $(OBJS) | $(BIN)
		$(FC) $(FFLAGS) $(CFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $^ -o $@
		$(RM) *.mod

$(LIB): $(FOBJS) | $(BIN)
		$(FC) $(LIBFLAGS) $(FFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $(FOBJS) -o $@

$(OBJ)/%.co: $(SRC)/%.c | $(OBJ)
		$(CC) $(CFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(OBJ)/%.fo: $(SRC)/%.F90 | $(OBJ)
		$(FC) $(FFLAGS) $(RELFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

-include $(DEPS)

debug: $(DBGEXE) $(DBGLIB)

$(DBGEXE): $(DBGOBJS) | $(DBGBIN)
		$(FC) $(FFLAGS) $(CFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $^ -o $@
		$(RM) *.mod

$(DBGLIB): $(DBGFOBJS) | $(DBGBIN)
		$(FC) $(LIBFLAGS) $(FFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) $(DBGFOBJS) -o $@

$(DBGOBJ)/%.co: $(SRC)/%.c | $(DBGOBJ)
		$(CC) $(CFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

$(DBGOBJ)/%.fo: $(SRC)/%.F90 | $(DBGOBJ)
		$(FC) $(FFLAGS) $(DBGFLAGS) -I$(INCLUDE) $(DEFINITIOS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@

-include $(DBGDEPS)

$(BIN) $(OBJ) $(DBGBIN) $(DBGOBJ):
		$(MKDIR) $@

clean:
		$(RM) $(OBJ) $(BIN) $(DBGBIN) $(DBGOBJ)
		$(RM) $(TESTDIR)/*.gcda
		$(RM) $(TESTDIR)/*.gcno
		$(RM) $(TESTDIR)/coverage.info
		$(RM) $(TESTDIR)/report
