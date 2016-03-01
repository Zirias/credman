define OBJRULES

$(T)_OBJDIR ?= $$(OBJDIR)$$(PSEP)$$($(T)_SRCDIR)

$(T)_SOURCES := $$(addprefix $$($(T)_SRCDIR)$$(PSEP), \
	$$(addsuffix .c,$$($(T)_MODULES)))
$(T)_OBJS := $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	$$(addsuffix .o,$$($(T)_MODULES)))
$(T)_SOBJS := $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	$$(addsuffix _s.o,$$($(T)_MODULES)))

ifneq ($$(strip $$($(T)_PLATFORMMODULES)),)
$(T)_SOURCES += $$(addprefix $$($(T)_SRCDIR)$$(PSEP), \
	$$(addsuffix _$$(PLATFORM).c,$$($(T)_PLATFORMMODULES)))
$(T)_OBJS += $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	$$(addsuffix _$$(PLATFORM).o,$$($(T)_PLATFORMMODULES)))
$(T)_SOBJS += $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	$$(addsuffix _$$(PLATFORM)_s.o,$$($(T)_PLATFORMMODULES)))
endif

ifeq ($$(PLATFORM),win32)
ifneq ($$(strip $$($(T)_win32_RES)),)
$(T)_SOURCES := $$(addprefix $$($(T)_SRCDIR)$$(PSEP), \
	$$(addsuffix .rc,$$($(T)_win32_RES)))
$(T)_OBJS := $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	$$(addsuffix .ro,$$($(T)_win32_RES)))

$$($(T)_OBJDIR)$$(PSEP)%.ro: $$($(T)_SRCDIR)$$(PSEP)%.rc \
    Makefile $$(CONFIG) | $$($(T)_OBJDIR)
	$$(VRES)
	$$(VR)$$(CROSS_COMPILE)windres $$^ $$@

endif
endif

CLEAN += $$($(T)_OBJS:.o=.d) $$($(T)_OBJS)

ifneq ($$(strip $$($(T)_OBJDIR)),$$(strip $$($(T)_SRCDIR)))
$$($(T)_OBJDIR):
	$$(VMD)
	$$(VR)$$(MDP) $$(addprefix $$($(T)_OBJDIR)$$(PSEP), \
	    $$(dir $$($(T)_MODULES))) 

endif

%.o: %.c

$$($(T)_OBJDIR)$$(PSEP)%.d: $$($(T)_SRCDIR)$$(PSEP)%.c \
	Makefile $$(CONFIG) | $$($(T)_OBJDIR)
	$$(VDEP)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -MM -MT"$$@ $$(@:.d=.o)" -MF$$@ \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_DEFINES) $$($(T)_DEFINES) $$(DEFINES) \
		$$($(T)_$$(PLATFORM)_INCLUDES) $$($(T)_INCLUDES) $$(INCLUDES) \
		$$<

ifneq ($$(MAKECMDGOALS),clean)
ifneq ($$(MAKECMDGOALS),distclean)
-include $$($(T)_OBJS:.o=.d)
endif
endif

$$($(T)_OBJDIR)$$(PSEP)%.o: $$($(T)_SRCDIR)$$(PSEP)%.c \
	Makefile $$(CONFIG) | $$($(T)_OBJDIR)
	$$(VCC)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -c -o$$@ \
		$$($(T)_$$(PLATFORM)_CFLAGS) $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_DEFINES) $$($(T)_DEFINES) $$(DEFINES) \
		$$($(T)_$$(PLATFORM)_INCLUDES) $$($(T)_INCLUDES) $$(INCLUDES) \
		$$<

$$($(T)_OBJDIR)$$(PSEP)%_s.o: $$($(T)_SRCDIR)$$(PSEP)%.c \
	Makefile $$(CONFIG) | $$($(T)_OBJDIR)
	$$(VCC)
	$$(VR)$$(CROSS_COMPILE)$$(CC) -c -o$$@ \
		$$($(T)_$$(PLATFORM)_CFLAGS_SHARED) $$($(T)_CFLAGS_SHARED) \
		$$(CFLAGS) \
		$$($(T)_$$(PLATFORM)_DEFINES) $$($(T)_DEFINES) $$(DEFINES) \
		$$($(T)_$$(PLATFORM)_INCLUDES) $$($(T)_INCLUDES) $$(INCLUDES) \
		$$<

endef

# vim: noet:si:ts=8:sts=8:sw=8
