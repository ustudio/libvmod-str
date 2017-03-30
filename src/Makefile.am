AM_CPPFLAGS = -I$(VARNISHSRC)/include -I$(VARNISHSRC)/bin/varnishd -I$(VARNISHSRC)

vmoddir = $(VMODDIR)

vmod_LTLIBRARIES = libvmod_str.la

libvmod_str_la_LDFLAGS = -module -export dynamic -avoid-version -shared
libvmod_str_la_SOURCES = vcc_if.c vcc_if.h vmod_str.c

vcc_if.c vcc_if.h: *.vcc
	@PYTHON@ @VMODTOOL@ $(top_srcdir)/src/vmod_str.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	$(VARNISHSRC)/bin/varnishtest/varnishtest -Dvarnishd=$(VARNISHSRC)/bin/varnishd/varnishd -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = vmod_str.vcc $(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
