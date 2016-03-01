P:=tests

T:=test_1
test_1_SRCDIR:= $(P)
test_1_MODULES:= test_1
test_1_LDFLAGS:= -L$(LIBDIR) -static
test_1_LIBS:= -lcmutils
test_1_DEPS:= $(LIBDIR)$(PSEP)libcmutils.a
test_1_BUILDWITH:= tests
test_t_STRIPWITH:=
$(eval $(BINRULES))

T:=test_2
test_2_SRCDIR:= $(P)
test_2_MODULES:= test_2
test_2_LDFLAGS:= -L$(LIBDIR) -static
test_2_LIBS:= -lcmmodel -lcmutils -lm
test_2_DEPS:= $(LIBDIR)$(PSEP)libcmmodel.a $(LIBDIR)$(PSEP)libcmutils.a
test_2_BUILDWITH:= tests
test_2_STRIPWITH:=
$(eval $(BINRULES))

