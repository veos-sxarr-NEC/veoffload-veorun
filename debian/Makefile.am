EXTRA_DIST = compat control.in copyright rules.in \
             veoffload-veorun.install.in \
             veoffload-veorun-dev.install.in

dist_noinst_DATA = control rules \
                   veoffload-veorun.install veoffload-veorun-dev.install

CLEANFILES = $(dist_noinst_DATA)

edit = $(SED) -e 's|@PACKAGE[@]|@PACKAGE@|g' \
              -e 's|@VERSION[@]|@VERSION@|g' \
              -e 's|@RELEASE[@]|@RELEASE@|g' \
              -e 's|@prefix[@]|@prefix@|g' \
              -e 's|@includedir[@]|@includedir@|g' \
              -e 's|@libdir[@]|@libdir@|g' \
              -e 's|@bindir[@]|@bindir@|g' \
              -e 's|@libexecdir[@]|@libexecdir@|g'

control: $(srcdir)/control.in Makefile
	$(edit) $< > $@

rules: $(srcdir)/rules.in Makefile
	$(edit) $< > $@
	chmod a+x $@

veoffload-veorun.install: $(srcdir)/veoffload-veorun.install.in Makefile
	$(edit) $< > $@

veoffload-veorun-dev.install: $(srcdir)/veoffload-veorun-dev.install.in Makefile
	$(edit) $< > $@
