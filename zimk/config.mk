#default config
CFG?=RELEASE
CFG:=$(strip $(CFG))

ifneq ($(CFG),RELEASE)
ifneq ($(CFG),DEBUG)
$(error Unknown CFG $(CFG))
endif
endif

ifeq ($(CFG),RELEASE)
CFGNAME:=release
else ifeq ($(CFG),DEBUG)
CFGNAME:=debug
DEFINES+=-DDEBUG
else
CFGNAME:=unknown
endif

CONFIG:=conf_$(CFGNAME).mk

# save / compare config
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
$(CONFIG):
	$(VGENT)
	$(VR)echo $(EQT)C_USECC := $(USECC)$(EQT) >$(CONFIG)
	$(VR)echo $(EQT)C_USECFLAGS := $(USECFLAGS)$(EQT) >>$(CONFIG)

-include $(CONFIG)

ifneq ($(strip $(C_USECC))_$(strip $(C_USECFLAGS)),$(strip $(USECC))_$(strip $(USECFLAGS)))
.PHONY: $(CONFIG)
endif
endif
endif

VTAGS:= [CFG=$(CFG)

ifneq ($(strip $(USECC)),)
CC:= $(USECC)
VTAGS+= USECC=$(CC)
endif

ifeq ($(CFG),DEBUG)
CFLAGS?= -std=c11 -Wall -Wextra -pedantic -g3 -O0
else
CFLAGS?= -std=c11 -Wall -Wextra -pedantic -g0 -O3
endif

ifneq ($(strip $(USECFLAGS)),)
CFLAGS+= $(USECFLAGS)
VTAGS+= USECFLAGS=$(strip $(USECFLAGS))
endif

VTAGS:= $(VTAGS)]

CLEAN+= $(CONFIG)

AR?=ar
STRIP?=strip

OBJBASEDIR?=obj
BINBASEDIR?=bin
LIBBASEDIR?=lib

OBJDIR?=$(OBJBASEDIR)$(PSEP)$(CFGNAME)
BINDIR?=$(BINBASEDIR)$(PSEP)$(CFGNAME)
LIBDIR?=$(LIBBASEDIR)$(PSEP)$(CFGNAME)

LDFLAGS?=-L$(LIBDIR)

# vim: noet:si:ts=8:sts=8:sw=8
