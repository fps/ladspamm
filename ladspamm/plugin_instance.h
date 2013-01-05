#ifndef LADSPAPP_LADSPA_PLUGIN_INSTANCE
#define LADSPAPP_LADSPA_PLUGIN_INSTANCE

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include <cmath>
#include <stdexcept>

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
		
		~plugin_instance()
		{
			the_plugin->descriptor->cleanup(handle);
		}
		
		plugin_ptr plugin()
		{
			return the_plugin;
		}
		

		void activate() 
		{
			if (NULL != the_plugin->descriptor->activate)
			{
				the_plugin->descriptor->activate(handle);
			}
		}
		
		void deactivate()
		{
			if (NULL != the_plugin->descriptor->deactivate)
			{
				the_plugin->descriptor->deactivate(handle);
			}
		}
		
		void connect_port(unsigned long port_index, LADSPA_Data *location)
		{
			the_plugin->descriptor->connect_port(handle, port_index, location);
		}
		
		LADSPA_Data port_lower_bound(unsigned int index)
		throw
		(
			std::logic_error
		)
		{
			if (false == the_plugin->port_is_bounded_below(index))
			{
				throw std::logic_error("Port has no lower bound");
			}
			
			if (true == the_plugin->port_is_scaled_by_samplerate(index))
			{
				return samplerate * the_plugin->port_lower_bound(index);
			}
			
			return the_plugin->port_lower_bound(index);
		}
		
		LADSPA_Data port_upper_bound(unsigned int index)
		throw
		(
			std::logic_error
		)
		{
			if (false == the_plugin->port_is_bounded_above(index))
			{
				throw std::logic_error("Port has no lower bound");
			}

			if (true == the_plugin->port_is_scaled_by_samplerate(index))
			{
				return samplerate * the_plugin->port_upper_bound(index);
			}
			
			return the_plugin->port_upper_bound(index);
		}
		
		LADSPA_Data port_default(unsigned int index)
		throw
		(
			std::logic_error
		)
		{
			if (false == the_plugin->port_has_default(index))
			{
				throw std::logic_error("Port has no default");
			}
			
			if (the_plugin->port_default_is_0(index))
			{
				return 0;
			}
			
			if (the_plugin->port_default_is_1(index))
			{
				return 1;
			}
			
			if (the_plugin->port_default_is_100(index))
			{
				return 100;
			}
			
			if (the_plugin->port_default_is_440(index))
			{
				return 440;
			}
			
			if (the_plugin->port_default_is_lower_bound(index))
			{
				return port_lower_bound(index);
			}

			if (the_plugin->port_default_is_upper_bound(index))
			{
				return port_upper_bound(index);
			}
		}
		
		void run(unsigned long nframes)
		{
			the_plugin->descriptor->run(handle, nframes);
		}
	};

	typedef boost::shared_ptr<plugin_instance> plugin_instance_ptr;
} // namespace
#endif
