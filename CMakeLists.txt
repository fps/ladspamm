cmake_minimum_required (VERSION 2.6)


# possible values: Release, Debug, RelWithDebugInfo
# set(CMAKE_BUILD_TYPE RelWithDebugInfo)

project(ladspamm)
set(PROJECT_VERSION "1")

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Florian Paul Schmidt (mista.tapas@gmx.net)")
set(CPACK_GENERATOR "DEB" "TGZ")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-filesystem, libboost-system")
include(CPack)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Native CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Native."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE off)

configure_file(ladspamm.pc.in ladspamm-${PROJECT_VERSION}.pc @ONLY)

add_definitions(-DPROJECT_VERSION=\"${PROJECT_VERSION}\")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wconversion -Wall -pthread -fmax-errors=1")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -pg")
endif()

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES RelWithDebugInfo)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES Native)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -mfpmath=sse")
    add_definitions("-DNDEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES NativeKvm)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -mfpmath=sse -mno-avx")
    add_definitions("-DNDEBUG")
endif()

message(STATUS "The build type is: " ${CMAKE_BUILD_TYPE})

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


#
# BUILD DEPENDENCIES:
#

# BOOST
set(Boost_USE_STATIC_LIBS)
find_package(Boost COMPONENTS filesystem system REQUIRED)

# 
# INSTALLATION
# 

install(FILES ladspamm/dl.h ladspamm/ladspamm.h ladspamm/library.h ladspamm/plugin.h ladspamm/plugin_instance.h ladspamm/world.h  DESTINATION include/ladspamm-${PROJECT_VERSION})
install(FILES ${PROJECT_BINARY_DIR}/ladspamm-${PROJECT_VERSION}.pc DESTINATION lib/pkgconfig)
