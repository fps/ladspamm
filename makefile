PREFIX ?= /usr/local

INSTALL ?= install
SED ?= sed

INCLUDE_PATH = $(PREFIX)/include/ladspamm-0
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install all clean

all: ladspamm-0-test built_python

install: all
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm-0.pc $(PKGCONFIG_DIR)/
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-0.pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm-0/*.h $(INCLUDE_PATH)
	python setup.py install

ladspamm-0-test: ladspamm-test.cc
	g++ -I .  -ansi -Wall -g -O0 -o ladspamm-0-test  ladspamm-test.cc -ldl -lboost_system -lboost_filesystem

docs:
	doxygen

built_python: ladspamm0.i
	swig -python -c++ -o ladspamm_wrap.cc ladspamm0.i
	python setup.py build_ext -ldl -lboost_system -lboost_filesystem -I .
	touch built_python

clean:
	rm -f _ladspamm0.so ladspamm_wrap.cc ladspamm-0-test ladspamm0.py built_python
	