# LADSPAMM

A C++ header only (out of pure laziness) library to find, inspect and instantiate LADSPA plugins.

# REQUIREMENTS

* boost-system

* boost-regex

* boost-filesystem

* LADSPA headers

* libdl

* sed

* make

# INSTALLATION

    make install

# TESTING

Build the test case with

    make test
    
and run it with

    ./ladspamm-0-test



# EXAMPLE

Checkout the ladspamm-test.cc file.

    #include <ladspamm-0/world.h>

    int main() 
    {
        ladspamm::world world;
    }

