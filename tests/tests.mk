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

