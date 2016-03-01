P:= model

T:= cmmodel
cmmodel_SRCDIR:= $(P)
cmmodel_MODULES:= cred
cmmodel_LDFLAGS:= -L$(LIBDIR)
cmmodel_LIBS:= -lcmutils
cmmodel_V_MAJ:= 0
cmmodel_V_MIN:= 0
cmmodel_V_REV:= 1
$(eval $(LIBRULES))

