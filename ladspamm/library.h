#ifndef LADSPAPP_LADSPA_LIBRARY_HH
#define LADSPAPP_LADSPA_LIBRARY_HH

#include <string>
#include <vector>
#include <dlfcn.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

#include <ladspamm-VERSION/plugin.h>

namespace ladspamm
{
	/**
	 * @brief Represents a LADSPA library file containing 
	 * (possibly) several plugins.
	 */
	struct library 
	: 
		boost::noncopyable 
	{
		dl_ptr the_dl;

		std::vector<plugin_ptr> plugins;
		
		/**
		 * @brief Constructs a library object using a dl object.
		 */
		library(dl_ptr the_dl) 
		throw 
		(
			std::runtime_error
		)
		:
			the_dl(the_dl)	
		{
			init();
		}
		
		/**
		 * @brief Constructs a library object from a given
		 * filename
		 */
		library(std::string filename)
		throw 
		(
			std::runtime_error
		)
		{
			the_dl = dl_ptr(new dl(filename));
			init();
		}
		
		void init()
		throw 
		(
			std::runtime_error
		)
		{
			LADSPA_Descriptor_Function descriptor_fun = (LADSPA_Descriptor_Function)dlsym(the_dl->dl_handle, "ladspa_descriptor");
			
			char *error = dlerror();
			if (NULL != error) {
				throw std::runtime_error("Failed to lookup descriptor. dlerror: " + std::string(error));
			}
			
			int index = 0;
			while(true) 
			{
				const LADSPA_Descriptor *descriptor;
				descriptor = descriptor_fun(index);
				if (0 == descriptor) 
				{
					break;
				}
				
				// std::cerr << "Plugin: " << descriptor->Label << std::endl;
				
				plugins.push_back(plugin_ptr(new plugin(the_dl, descriptor)));
				++index;
			}
		}
	};
	
	typedef boost::shared_ptr<library> library_ptr;
} // namespace

#endif
