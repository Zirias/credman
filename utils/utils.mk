P:=utils

T:=cmutils
cmutils_SRCDIR:= $(P)
cmutils_MODULES:= common int logger stringbuilder serializer jsonser
cmutils_PLATFORMMODULES:= common
cmutils_V_MAJ:= 0
cmutils_V_MIN:= 0
cmutils_V_REV:= 1
$(eval $(LIBRULES))

# vim: noet:si:ts=8:sts=8:sw=8
