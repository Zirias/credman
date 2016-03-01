P:=utils

T:=test_1
test_1_SRCDIR:= $(P)
test_1_MODULES:= common int logger stringbuilder test_1

$(eval $(BINRULES))

# vim: noet:si:ts=8:sts=8:sw=8
