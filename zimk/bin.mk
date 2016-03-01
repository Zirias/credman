define BINRULES
$(OBJRULES)

$(T)_TARGET ?= $(T)
$(T)_TGTDIR ?= $$(BINDIR)
$(T)_BUILDWITH ?= all
$(T)_STRIPWITH ?= strip

ifneq ($$(strip $$($(T)_TGTDIR)),$$(strip $$($(T)_SRCDIR)))
$$($(T)_TGTDIR):
	$$(VMD)
	$$(VR)$$(MDP) $$($(T)_TGTDIR)

endif

ifneq ($$(strip $$($(T)_BUILDWITH)),)
$$($(T)_BUILDWITH): $$($(T)_TGTDIR)$$(PSEP)$$($(T)_TARGET)$$(EXE)

endif

ifneq ($$(strip $$($(T)_STRIPWITH)),)
$$($(T)_STRIPWITH): $$($(T)_TGTDIR)$$(PSEP)$$($(T)_TARGET)$$(EXE)
	$$(VSTRP)
	$$(VR)$$(CROSS_COMPILE)strip --strip-all $$<

endif

$$($(T)_TGTDIR)$$(PSEP)$$($(T)_TARGET): $$($(T)_OBJS) \
	$$($(T)_$$(PLATFORM)_LIBS) $$($(T)_LIBS) | $$($(T)_TGTDIR)
	$$(VCCLD)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -o$$@ \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_LDFLAGS) $$($(T)_LDFLAGS) $$(LDFLAGS) \
		$$($(T)_OBJS) $$($(T)_$$(PLATFORM)_LIBS) $$($(T)_LIBS)

endef

# vim: noet:si:ts=8:sts=8:sw=8
