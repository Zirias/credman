all::

ifeq ($(OS),Windows_NT)

SYSNAME := Windows

EXE := .exe
CMDSEP := &
PSEP := \\
CPF := copy /y
RMF := del /f /q
RMFR := -rd /s /q
MDP := -md
XIF := if exist
XTHEN := (
XFI := )
CATIN := copy /b
CATADD := +
CATOUT :=
EQT :=
CMDQUIET := >nul 2>nul & verify >nul

PLATFORM := win32

else

SYSNAME := $(shell uname)

EXE :=
CMDSEP := ;
PSEP := /
CPF := cp -f
RMF := rm -f
RMFR := rm -fr
MDP := mkdir -p
XIF := if [ -x
XTHEN := ]; then
XFI := ; fi
CATIN := cat
CATADD := 
CATOUT := >
EQT := "
#" make vim syntax highlight happy
CMDQUIET := >/dev/null 2>&1

PLATFORM := posix

endif

ZIMKPATH:=$(subst .mk,,$(lastword $(MAKEFILE_LIST)))

include $(ZIMKPATH)$(PSEP)silent.mk
include $(ZIMKPATH)$(PSEP)config.mk
include $(ZIMKPATH)$(PSEP)objs.mk
include $(ZIMKPATH)$(PSEP)bin.mk
include $(ZIMKPATH)$(PSEP)lib.mk

clean::
	$(RMF) $(CLEAN)

distclean::
	$(RMFR) $(BINBASEDIR)
	$(RMFR) $(LIBBASEDIR)
	$(RMFR) $(OBJBASEDIR)

strip:: all

.PHONY: all strip clean distclean

# vim: noet:si:ts=8:sts=8:sw=8
