define BINRULES
$(OBJRULES)

$(T)_TARGET ?= $(T)
$(T)_TGTDIR ?= $$(BINDIR)
$(T)_BUILDWITH ?= all
$(T)_STRIPWITH ?= strip

ifneq ($$(strip $$($(T)_TGTDIR)),$$(strip $$($(T)_SRCDIR)))
_BINDIRS_+=$$($(T)_TGTDIR)
$$($(T)_TGTDIR): $$(BINDIR)$$(PSEP).bindirs

endif

$(BUILDDEPS)
$(LINKFLAGS)

$(T)_EXE := $$($(T)_TGTDIR)$$(PSEP)$$($(T)_TARGET)$$(EXE)

$(T): $$($(T)_EXE)

.PHONY: $(T)

ifneq ($$(strip $$($(T)_BUILDWITH)),)
$$($(T)_BUILDWITH):: $$($(T)_EXE)

endif

ifneq ($$(strip $$($(T)_STRIPWITH)),)
$$($(T)_STRIPWITH):: $$($(T)_EXE)
	$$(VSTRP)
	$$(VR)$$(CROSS_COMPILE)$$(STRIP) --strip-all $$<

endif

$$($(T)_EXE): $$($(T)_OBJS) $$(_$(T)_DEPS) \
	| $$($(T)_TGTDIR)
	$$(VCCLD)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -o$$@ \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_LDFLAGS) $$($(T)_LDFLAGS) $$(LDFLAGS) \
		$$($(T)_OBJS) $$(_$(T)_LINK)

endef

$(BINDIR)$(PSEP).bindirs:
	$(VR)$(MDP) $(sort $(BINDIR) $(_BINDIRS_))
	$(VR)$(STAMP) $@

# vim: noet:si:ts=8:sts=8:sw=8
