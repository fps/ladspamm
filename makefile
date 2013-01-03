PREFIX ?= /usr/local

INSTALL ?= install
SED ?= sed

VERSION = 0

INCLUDE_PATH = $(PREFIX)/include/ladspamm-$(VERSION)
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install

all: test

install:
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm.pc $(PKGCONFIG_DIR)/ladspamm-$(VERSION).pc
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-$(VERSION).pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm/*.h $(INCLUDE_PATH)
	for header in $(INCLUDE_PATH)/*.h; do sed -i -e s@VERSION@$(VERSION)@g "$$header"; done

test: ladspamm-test.cc
	PREFIX=./test make install
	g++ -o ladspamm-$(VERSION)-test  ladspamm-test.cc `PKG_CONFIG_PATH=./test/lib/pkgconfig pkg-config ladspamm-$(VERSION) --cflags --libs`

