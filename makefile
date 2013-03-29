PREFIX ?= /usr/local

INSTALL ?= install
SED ?= sed

INCLUDE_PATH = $(PREFIX)/include/ladspamm-0
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install all test

all: test

install:
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm.pc $(PKGCONFIG_DIR)/ladspamm-0.pc
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-0.pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm-0/*.h $(INCLUDE_PATH)

test: ladspamm-test.cc
	g++ -ansi -Wall -g -O0 -o ladspamm-0-test  ladspamm-test.cc -ldl

docs:
	PREFIX=./test make install
	doxygen

