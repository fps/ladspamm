#ifndef LADSPA_PLUGIN_HH
#define LADSPA_PLUGIN_HH

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <ladspa.h>
#include <iostream>

#include <ladspamm-VERSION/dl.h>

namespace ladspamm 
{
	struct plugin
	:
		boost::noncopyable
	{
		dl_ptr the_dl;
		const LADSPA_Descriptor *descriptor;
		
		plugin(dl_ptr the_dl, const LADSPA_Descriptor *descriptor)
		throw 
		(
			std::runtime_error
		)
		:
			the_dl(the_dl),
			descriptor(descriptor)
		{
			// std::cerr << uid() << "\t" << label() << "\t" << name() << " " << maker() << std::endl;
		}
		
		std::string label() 
		{
			return descriptor->Label;
		}
		
		std::string name()
		{
			return descriptor->Name;
		}
		
		std::string maker()
		{
			return descriptor->Maker;
		}
		
		unsigned long uid()
		{
			return descriptor->UniqueID;
		}
		
		unsigned long port_count()
		{
			return descriptor->PortCount;
		}
		
		std::string port_name(unsigned int index)
		{
			return descriptor->PortNames[index];
		}
	};
	
	typedef boost::shared_ptr<plugin> plugin_ptr;
} // namespace

#endif
