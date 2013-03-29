PREFIX ?= /usr/local

INSTALL ?= install

INCLUDE_PATH = $(PREFIX)/include/ladspamm-0
PKGCONFIG_DIR ?= $(PREFIX)/lib/pkgconfig

.PHONY: install all clean

all: test python_swig

install: all
	$(INSTALL) -d $(PKGCONFIG_DIR)
	$(INSTALL) ladspamm.pc $(PKGCONFIG_DIR)/ladspamm-0.pc
	$(SED) -i -e s@PREFIX@$(PREFIX)@g $(PKGCONFIG_DIR)/ladspamm-0.pc 
	$(INSTALL) -d $(INCLUDE_PATH)
	$(INSTALL) ladspamm-0/*.h $(INCLUDE_PATH)

test: ladspamm-test.cc
	g++ -ansi -Wall -g -O0 -o ladspamm-0-test  ladspamm-test.cc -ldl -lboost_system -lboost_filesystem

docs:
	doxygen

python_swig: ladspamm0.i
	swig -python -c++ -o ladspamm_wrap.cc ladspamm0.i
	g++ -fPIC -shared -o ladspamm0.so ladspamm_wrap.cc `pkg-config python-2.7 --cflags --libs` -ldl -lboost_system -lboost_filesystem

clean:
	rm -f ladspamm0.so ladspamm_wrap.cc ladspamm-0-test ladspamm0.py