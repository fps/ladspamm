#ifndef LADSPAPP_LADSPA_PLUGIN_INSTANCE
#define LADSPAPP_LADSPA_PLUGIN_INSTANCE

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>

#include <ladspamm-VERSION/plugin.h>

namespace ladspamm
{
	struct plugin_instance 
	: 
		boost::noncopyable 
	{
		plugin_ptr the_plugin;
		LADSPA_Handle handle;
		unsigned long samplerate;
		
		plugin_instance
		(
			plugin_ptr the_plugin,
			unsigned long samplerate
		)
		throw 
		(
			std::runtime_error
		)
		:
			the_plugin(the_plugin),
			samplerate(samplerate)
		{
			handle = the_plugin->descriptor->instantiate(the_plugin->descriptor, samplerate);
			
			if (NULL == handle)
			{
				throw std::runtime_error("Failed to instantiate plugin");
			}
		}
		
		void activate() 
		{
			the_plugin->descriptor->activate(handle);
		}
		
		void deactivate()
		{
			the_plugin->descriptor->deactivate(handle);
		}
		
		void connect_port(unsigned long port, LADSPA_Data *location)
		{
			the_plugin->descriptor->connect_port(handle, port, location);
		}
	};

	typedef boost::shared_ptr<plugin_instance> plugin_instance_ptr;
} // namespace
#endif
