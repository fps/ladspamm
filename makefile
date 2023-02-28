PREFIX ?= /usr/local
CXXFLAGS ?= -O2 -g -pedantic -Wall -Werror -std=c++11 -I.
LDFLAGS ?= -lboost_filesystem
VALGRIND_FLAGS ?= --leak-check=full  --show-leak-kinds=all

install:
	install -d ${PREFIX}/include/ladspamm1
	install ladspamm1/* ${PREFIX}/include/ladspamm1/

test: ladspamm-test ladspamm-test2
	valgrind ${VALGRIND_FLAGS} ./ladspamm-test
	valgrind ${VALGRIND_FLAGS} ./ladspamm-test2
