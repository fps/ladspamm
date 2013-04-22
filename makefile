PREFIX ?= /usr/local

INSTALL ?= install
SED ?= sed

INCLUDE_PATH = $(PREFIX)/include/ladspamm-0
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install all clean

all: ladspamm-0-test

install: all
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm-0.pc $(PKGCONFIG_DIR)/
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-0.pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm-0/*.h $(INCLUDE_PATH)

ladspamm-0-test: ladspamm-test.cc
	g++ -I .  -ansi -Wall -g -O0 -o ladspamm-0-test  ladspamm-test.cc -ldl -lboost_filesystem -lboost_system 

docs:
	doxygen

clean:
	rm -f ladspamm-0-test
	
