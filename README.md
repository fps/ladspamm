# LADSPAMM

A C++ header only (out of pure laziness) library to find, inspect and instantiate LADSPA plugins.

# REQUIREMENTS

* boost-system

* boost-filesystem

* LADSPA headers

* libdl

* sed

* make

# INSTALLATION

If you don't want to use cmake's package creation facility, use the standard way:

    mkdir bld
    cd bld
    cmake ..
    make 
    make install

But you can also create .tgz and .deb packages:

    mkdir bld
    cd bld
    cmake ..
    make package
    dpkg -i ladspamm-1-Linux.deb


# TESTING

Build the example program with

    make test
    
and run it with

    ./ladspamm-0-test

# EXAMPLE

Checkout the ladspamm-test.cc file for some usage info.

# DOCUMENTATION

Use the source, Luke! But besides that there should also be a doxygen documentation at http://fps.github.com/ladspamm

# AUTHOR

Florian Paul Schmidt (mista.tapas at gmx dot net)

# LICENSE

LGPL 3.0 or higher (see http://www.gnu.org/copyleft/lesser.html) and the LICENSE file in the source..
