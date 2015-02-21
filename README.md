# LADSPAMM

A C++ header only (out of pure laziness) library to find, inspect and instantiate LADSPA plugins.

# REQUIREMENTS

* boost-system

* boost-filesystem

* LADSPA headers

* libdl

* cmake 2.8

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


# EXAMPLE

Checkout the ladspamm-test.cc.in file for an example listing installed LADSPA plugins and some of their properties.

# DOCUMENTATION

Use the source, Luke! But besides that there should also be a doxygen documentation at http://fps.github.com/ladspamm

# AUTHOR

Florian Paul Schmidt (mista.tapas at gmx dot net)

# LICENSE

LGPL 3.0 or higher (see http://www.gnu.org/copyleft/lesser.html) and the LICENSE file in the source..
