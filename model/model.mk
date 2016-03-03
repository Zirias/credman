P:= model

T:= cmmodel
cmmodel_SRCDIR:= $(P)
cmmodel_MODULES:= cred
cmmodel_DEPS:= cmutils
cmmodel_LIBS:= cmutils
cmmodel_V_MAJ:= 0
cmmodel_V_MIN:= 0
cmmodel_V_REV:= 1
$(eval $(LIBRULES))

# vim: noet:si:ts=8:sts=8:sw=8
