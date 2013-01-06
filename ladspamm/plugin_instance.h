#ifndef LADSPAPP_LADSPA_PLUGIN_INSTANCE
#define LADSPAPP_LADSPA_PLUGIN_INSTANCE

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include <cmath>
#include <algorithm>
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
			if (NULL != the_plugin->descriptor->cleanup)
			{
				the_plugin->descriptor->cleanup(handle);
			}
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
		
		/**
		 * This function tries to do an educated
		 * guess when the plugin does silly things like
		 * specifying default values outside of bounds
		 * or no default at all
		 */
		LADSPA_Data port_default_guessed(unsigned int index)
		{
			LADSPA_Data guess = 0;
			
			if (the_plugin->port_has_default(index))
			{
				guess = port_default(index);
			}
			
			if (the_plugin->port_is_bounded_below(index))
			{
				guess = std::max(port_lower_bound(index), guess);
			}
			
			if (the_plugin->port_is_bounded_above(index))
			{
				guess = std::min(port_upper_bound(index), guess);
			}
			
			return guess;
		}
		
		LADSPA_Data port_default(unsigned int index)
		{
			if (the_plugin->port_is_integer(index))
			{
				return round(port_default0(index));
			}
			else
			{
				return port_default0(index);
			}
		}
		
		LADSPA_Data port_default0(unsigned int index)
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
			
			if (the_plugin->port_default_is_middle(index))
			{
				if (the_plugin->port_is_logarithmic(index))
				{
					return exp(log(the_plugin->port_lower_bound(index)) * 0.5 + log(the_plugin->port_upper_bound(index)) * 0.5);
				}
				else
				{
					return the_plugin->port_lower_bound(index) * 0.5 + the_plugin->port_upper_bound(index) * 0.5;
				}
			}
			
			if (the_plugin->port_default_is_low(index))
			{
				if (the_plugin->port_is_logarithmic(index))
				{
					return exp(log(the_plugin->port_lower_bound(index)) * 0.75 + log(the_plugin->port_upper_bound(index)) * 0.25);
				}
				else
				{
					return the_plugin->port_lower_bound(index) * 0.75 + the_plugin->port_upper_bound(index) * 0.25;
				}
			}

			if (the_plugin->port_default_is_high(index))
			{
				if (the_plugin->port_is_logarithmic(index))
				{
					return exp(log(the_plugin->port_lower_bound(index)) * 0.25 + log(the_plugin->port_upper_bound(index)) * 0.75);
				}
				else
				{
					return the_plugin->port_lower_bound(index) * 0.25 + the_plugin->port_upper_bound(index) * 0.75;
				}
			}

			throw std::logic_error("Unhandled default case - this is a bug in ladspamm. Please report to the author..");
		}
		
		void run(unsigned long nframes)
		{
			the_plugin->descriptor->run(handle, nframes);
		}
	};

	typedef boost::shared_ptr<plugin_instance> plugin_instance_ptr;
} // namespace
#endif
