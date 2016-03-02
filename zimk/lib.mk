define LIBRULES
$(OBJRULES)

$(T)_TARGET ?= $(T)
$(T)_V_MAJ ?= 1
$(T)_V_MIN ?= 0
$(T)_V_REV ?= 0
$(T)_TGTDIR ?= $$(LIBDIR)
$(T)_BINDIR ?= $$(BINDIR)
$(T)_CFLAGS_SHARED ?= $$($(T)_CFLAGS) -fPIC
$(T)_BUILDWITH ?= all
$(T)_BUILDSTATICWITH ?= staticlibs
$(T)_STRIPWITH ?= strip

_$(T)_STATIC:= $$($(T)_TGTDIR)$$(PSEP)lib$(T).a

$(LINKFLAGS)

ifeq ($$(PLATFORM),win32)
_$(T)_SHARED:= $$($(T)_BINDIR)$$(PSEP)$(T)-$$($(T)_V_MAJ).dll

$$(_$(T)_STATIC): $$(_$(T)_SHARED)

$$(_$(T)_SHARED): $$($(T)_SOBJS) $$($(T)_DEPS) | $$($(T)_TGTDIR) $$($(T)_BINDIR)
	$$(VCCLD)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -shared -o$$@ \
		-Wl,--out-implib,$$($(T)_TGTDIR)$$(PSEP)lib$(T).a \
		-Wl,--output-def,$$($(T)_TGTDIR)$$(PSEP)$(T).def \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_LDFLAGS) $$($(T)_LDFLAGS) $$(LDFLAGS) \
		$$($(T)_SOBJS) $$(_$(T)_LINK)

else
_$(T)_V:= $$($(T)_V_MAJ).$$($(T)_V_MIN).$$($(T)_V_REV)
_$(T)_SHARED_FULL:= $$($(T)_TGTDIR)$$(PSEP)lib$(T).so.$$(_$(T)_V)
_$(T)_SHARED_MAJ:= $$($(T)_TGTDIR)$$(PSEP)lib$(T).so.$$($(T)_V_MAJ)
_$(T)_SHARED:= $$($(T)_TGTDIR)$$(PSEP)lib$(T).so

$$(_$(T)_STATIC): $$($(T)_OBJS) $$($(T)_STATICDEPS) | $$($(T)_TGTDIR)
	$$(VAR)
	$$(VR)$$(CROSS_COMPILE)$$(AR) rcs $$@ $$^

$$(_$(T)_SHARED): $$(_$(T)_SHARED_MAJ)
	$$(VR)ln -fs lib$(T).so.$$($(T)_V_MAJ) $$@

$$(_$(T)_SHARED_MAJ): $$(_$(T)_SHARED_FULL)
	$$(VR)ln -fs lib$(T).so.$$(_$(T)_V) $$@

$$(_$(T)_SHARED_FULL): $$($(T)_SOBJS) $$($(T)_DEPS) | $$($(T)_TGTDIR)
	$$(VCCLD)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -shared -o$$@ \
		-Wl,-soname,lib$(T).so.$$($(T)_V_MAJ) \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_LDFLAGS) $$($(T)_LDFLAGS) $$(LDFLAGS) \
		$$($(T)_SOBJS) $$(_$(T)_LINK)

endif

ifneq ($$(strip $$($(T)_TGTDIR)),$$(strip $$($(T)_SRCDIR)))
$$($(T)_TGTDIR)::
	$$(VMD)
	$$(VR)$$(MDP) $$($(T)_TGTDIR)

endif

ifneq ($$(strip $$($(T)_BUILDWITH)),)
$$($(T)_BUILDWITH):: $$(_$(T)_SHARED)

endif

ifneq ($$(strip $$($(T)_BUILDSTATICWITH)),)
$$($(T)_BUILDSTATICWITH):: $$(_$(T)_STATIC)

endif

ifneq ($$(strip $$($(T)_STRIPWITH)),)
$$($(T)_STRIPWITH):: $$(_$(T)_SHARED)
	$$(VSTRP)
	$$(VR)$$(CROSS_COMPILE)$$(STRIP) --strip-unneeded $$<

ifneq ($$(strip $$($(T)_BUILDSTATICWITH)),)
$$($(T)_STRIPWITH):: $$(_$(T)_STATIC)
	$$(VSTRP)
	$$(VR)$$(CROSS_COMPILE)$$(STRIP) --strip-unneeded $$<


endif

endif

endef

# vim: noet:si:ts=8:sts=8:sw=8
