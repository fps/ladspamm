%module ladspamm0
%include <std_string.i>
%include <std_vector.i>
%include <boost_shared_ptr.i>

%shared_ptr (ladspamm::library)
%shared_ptr (ladspamm::plugin)
%shared_ptr (ladspamm::dl)

%{
#include "ladspamm-0/dl.h"
#include "ladspamm-0/plugin.h"
#include "ladspamm-0/plugin_instance.h"
#include "ladspamm-0/library.h"
#include "ladspamm-0/world.h"
%}

%template (library_p) boost::shared_ptr<ladspamm::library>;
%template (library_vector) std::vector<boost::shared_ptr<ladspamm::library> >;

%template (plugin_p) boost::shared_ptr<ladspamm::plugin>;
%template (plugin_vector) std::vector<boost::shared_ptr<ladspamm::plugin> >;

%include "ladspamm-0/dl.h"
%include "ladspamm-0/plugin.h"
%include "ladspamm-0/plugin_instance.h"
%include "ladspamm-0/library.h"
%include "ladspamm-0/world.h"



