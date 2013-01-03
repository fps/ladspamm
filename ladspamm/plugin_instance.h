#ifndef LADSPAPP_LADSPA_PLUGIN_INSTANCE
#define LADSPAPP_LADSPA_PLUGIN_INSTANCE

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include "ladspa_library.h"

#include <ladspa_plugin.h>

namespace ladspapp 
{
	struct ladspa_plugin_instance 
	: 
		boost::noncopyable 
	{
		ladspa_plugin_ptr the_ladspa_plugin;
		LADSPA_Handle handle;
		
		ladspa_plugin_instance
		(
			ladspa_plugin_ptr the_ladspa_plugin,
			unsigned long samplerate
		)
		throw 
		(
			std::runtime_error
		)
		:
			the_ladspa_plugin(the_ladspa_plugin)
		{
				handle = the_ladspa_plugin->descriptor->instantiate(the_ladspa_plugin->descriptor, samplerate);
		}
	};

	typedef boost::shared_ptr<ladspa_plugin_instance> ladspa_plugin_instance_ptr;
} // namespace
#endif
