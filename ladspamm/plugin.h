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
		
		bool port_is_input(unsigned int index)
		{
			return LADSPA_IS_PORT_INPUT(descriptor->PortDescriptors[index]);
		}

		bool port_is_output(unsigned int index)
		{
			return LADSPA_IS_PORT_OUTPUT(descriptor->PortDescriptors[index]);
		}

		bool port_is_control(unsigned int index)
		{
			return LADSPA_IS_PORT_AUDIO(descriptor->PortDescriptors[index]);
		}

		bool port_is_audio(unsigned int index)
		{
			return LADSPA_IS_PORT_CONTROL(descriptor->PortDescriptors[index]);
		}

		bool port_is_bounded_below(unsigned int index)
		{
			return LADSPA_IS_HINT_BOUNDED_BELOW(descriptor->PortRangeHints[index].HintDescriptor);
		}
		
		LADSPA_Data port_lower_bound(unsigned int index)
		{
			return descriptor->PortRangeHints[index].LowerBound;
		}

		LADSPA_Data port_upper_bound(unsigned int index)
		{
			return descriptor->PortRangeHints[index].UpperBound;
		}

		bool port_is_bounded_above(unsigned int index)
		{
			return LADSPA_IS_HINT_BOUNDED_BELOW(descriptor->PortRangeHints[index].HintDescriptor);
		}
		
		bool port_is_scaled_by_samplerate(unsigned int index)
		{
			return LADSPA_IS_HINT_SAMPLE_RATE(descriptor->PortRangeHints[index].HintDescriptor);
		}
		
		bool port_is_logarithmic(unsigned int index)
		{
			return LADSPA_IS_HINT_LOGARITHMIC(descriptor->PortRangeHints[index].HintDescriptor);
		}
		
		bool port_is_integer(unsigned int index)
		{
			return LADSPA_IS_HINT_INTEGER(descriptor->PortRangeHints[index].HintDescriptor);
		}

		bool port_is_toggled(unsigned int index)
		{
			return LADSPA_IS_HINT_TOGGLED(descriptor->PortRangeHints[index].HintDescriptor);
		}

		bool port_has_default(unsigned int index)
		{
			return LADSPA_IS_HINT_HAS_DEFAULT(descriptor->PortRangeHints[index].HintDescriptor);
		}
		
		bool port_default_is_0(unsigned int index)
		{
			return LADSPA_IS_HINT_DEFAULT_0(descriptor->PortRangeHints[index].HintDescriptor);
		}

		bool port_default_is_1(unsigned int index)
		{
			return LADSPA_IS_HINT_DEFAULT_1(descriptor->PortRangeHints[index].HintDescriptor);
		}

		bool port_default_is_100(unsigned int index)
		{
			return LADSPA_IS_HINT_DEFAULT_100(descriptor->PortRangeHints[index].HintDescriptor);
		}

		bool port_default_is_440(unsigned int index)
		{
			return LADSPA_IS_HINT_DEFAULT_440(descriptor->PortRangeHints[index].HintDescriptor);
		}

	};
	
	typedef boost::shared_ptr<plugin> plugin_ptr;
} // namespace

#endif
