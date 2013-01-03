# LADSPAMM

A C++ header only library to find, inspect and instantiate LADSPA plugins.

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

    make test



# EXAMPLE

Checkout the ladspamm-test.cc file.

    #include <ladspamm-0/world.h>

    int main() 
    {
        ladspamm::world world;
    }

