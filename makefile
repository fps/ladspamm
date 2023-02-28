PREFIX ?= /usr/local
CXXFLAGS ?= -O2 -g -pedantic -Wall -Werror -std=c++11 -I. ${ADDITIONAL_CXXFLAGS}
LDFLAGS ?= -lboost_filesystem ${ADDITIONAL_LDFLAGS}
VALGRIND_FLAGS ?= --leak-check=full  --show-leak-kinds=all ${ADDITIONAL_VALGRIND_FLAGS}

test: ladspamm-test ladspamm-test2
	valgrind ${VALGRIND_FLAGS} ./ladspamm-test
	valgrind ${VALGRIND_FLAGS} ./ladspamm-test2

install:
	install -d ${PREFIX}/include/ladspamm1
	install ladspamm1/* ${PREFIX}/include/ladspamm1/
	install -d ${PREFIX}/lib/pkgconfig
	install ladspamm1.pc ${PREFIX}/lib/pkgconfig
	sed -i "s|@INSTALL_PREFIX@|${PREFIX}|g" ${PREFIX}/lib/pkgconfig/ladspamm1.pc
