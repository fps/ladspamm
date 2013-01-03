#ifndef LADSPAPP_LADSPA_LIBRARY_HH
#define LADSPAPP_LADSPA_LIBRARY_HH

#include <string>
#include <vector>
#include <dlfcn.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

#include <ladspa_plugin.h>
#include <library.h>

namespace ladspapp 
{
	/**
	* A simple wrapper class around a LADSPA library file
	* to make some reoccuring work easier..
	*/
	struct ladspa_library 
	: 
		boost::noncopyable 
	{
		library_ptr the_library;

		std::vector<ladspa_plugin_ptr> ladspa_plugins;
		
		ladspa_library(library_ptr the_library) 
		throw 
		(
			std::runtime_error
		)
		:
			the_library(the_library)	
		{
			init();
		}
		
		ladspa_library(std::string filename)
		throw 
		(
			std::runtime_error
		)
		{
			the_library = library_ptr(new library(filename));
			init();
		}
		
		void init()
		throw 
		(
			std::runtime_error
		)
		{
			LADSPA_Descriptor_Function ladspa_descriptor_fun = (LADSPA_Descriptor_Function)dlsym(the_library->dl, "ladspa_descriptor");
			
			char *error = dlerror();
			if (NULL != error) {
				throw std::runtime_error("Failed to lookup ladspa_descriptor. dlerror: " + std::string(error));
			}
			
			int index = 0;
			while(true) 
			{
				const LADSPA_Descriptor *descriptor;
				descriptor = ladspa_descriptor_fun(index);
				if (0 == descriptor) 
				{
					break;
				}
				
				// std::cerr << "Plugin: " << descriptor->Label << std::endl;
				
				ladspa_plugins.push_back(ladspa_plugin_ptr(new ladspa_plugin(the_library, descriptor)));
				++index;
			}
		}
	};
	
	typedef boost::shared_ptr<ladspa_library> ladspa_library_ptr;
} // namespace

#endif
