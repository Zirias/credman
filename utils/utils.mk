P:=utils

T:=cmutils
cmutils_SRCDIR:= $(P)
cmutils_MODULES:= common int logger stringbuilder
$(eval $(LIBRULES))

# vim: noet:si:ts=8:sts=8:sw=8
