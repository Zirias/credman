include zimk.mk

INCLUDES:= -I.$(PSEP)include

include utils$(PSEP)utils.mk
include tests$(PSEP)tests.mk

# vim: noet:si:ts=8:sts=8:sw=8
