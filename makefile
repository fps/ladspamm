PREFIX ?= /usr/local

INSTALL ?= install

INCLUDE_PATH = $(PREFIX)/include/ladspamm-0
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install all clean

all: ladspamm-0-test _ladspamm0.so

install: all
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm.pc $(PKGCONFIG_DIR)/ladspamm-0.pc
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-0.pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm-0/*.h $(INCLUDE_PATH)

ladspamm-0-test: ladspamm-test.cc
	g++ -ansi -Wall -g -O0 -o ladspamm-0-test  ladspamm-test.cc -ldl -lboost_system -lboost_filesystem

docs:
	doxygen

_ladspamm0.so: ladspamm0.i
	swig -python -c++ -o ladspamm_wrap.cc ladspamm0.i
	python setup.py  build_ext --inplace -ldl -lboost_system -lboost_filesystem -I .

clean:
	rm -f _ladspamm0.so ladspamm_wrap.cc ladspamm-0-test ladspamm0.py
	