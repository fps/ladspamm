%module ladspamm0
%{
#include <ladspamm-0/world.h>
#include <ladspamm-0/plugin.h>
#include <ladspamm-0/library.h>
%}

%include "std_string.i"
%include "std_vector.i"

namespace std {
	%template(library_vector) vector<ladspamm::library_ptr>;
	%template(plugin_vector) vector<ladspamm::plugin_ptr>;
}

%include <ladspamm-0/world.h>
#include <ladspamm-0/plugin.h>
#include <ladspamm-0/library.h>

