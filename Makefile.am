lib_LIBRARIES = libveorun.a
libexec_PROGRAMS = veorun
libexec_SCRIPTS = mk_veorun_static
veorunheadersdir = $(includedir)/veorun
veorunheaders_HEADERS = veorun.h veo_private_defs.h
EXTRA_DIST = veorun.spec.in mk_veorun_static.in
dist_noinst_DATA = veorun.spec
CLEANFILES = veorun.spec mk_veorun_static
SUBDIRS = debian
veorun_SOURCES = veorun.c veo_block.S dummy.c
libveorun_a_SOURCES = veorun.c veo_block.S dummy.c

edit = $(SED) -e 's|@PACKAGE[@]|@PACKAGE@|g' \
              -e 's|@VERSION[@]|@VERSION@|g' \
              -e 's|@RELEASE[@]|@RELEASE@|g' \
              -e 's|@CC[@]|@CC@|g' \
              -e 's|@prefix[@]|@prefix@|g' \
	      -e 's|@libdir[@]|@libdir@|g' \
              -e 's|@libexecdir[@]|@libexecdir@|g' \
              -e 's|@includedir[@]|@includedir@|g'

veorun.spec: $(srcdir)/veorun.spec.in Makefile
	$(edit) $< > $@

mk_veorun_static: $(srcdir)/mk_veorun_static.in Makefile
	$(edit) $< > $@

print-distdir:
	@echo $(distdir)
print-package:
	@echo $(PACKAGE)
print-version:
	@echo $(VERSION)
