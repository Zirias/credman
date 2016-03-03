P:=tests

T:=test_1
test_1_SRCDIR:= $(P)
test_1_MODULES:= test_1
test_1_STATICLIBS:= cmutils
test_1_STATICDEPS:= cmutils
test_1_BUILDWITH:= tests
test_1_STRIPWITH:=
$(eval $(BINRULES))

T:=test_2
test_2_SRCDIR:= $(P)
test_2_MODULES:= test_2
test_2_LIBS:= m
test_2_STATICLIBS:= cmmodel cmutils
test_2_STATICDEPS:= cmmodel cmutils
test_2_BUILDWITH:= tests
test_2_STRIPWITH:=
$(eval $(BINRULES))

