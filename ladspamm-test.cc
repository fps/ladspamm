#include <ladspamm-0/world.h>
#include <ladspamm-0/plugin_instance.h>

#include <iostream>
#include <cstdlib>

int main() 
{
	try
	{
		ladspamm::world world;
		
		ladspamm::plugin_instance instance(world.libraries[0]->plugins[0], 48000);
		
		std::cout << "Name: " << instance.plugin()->name() << std::endl;
		
		for (unsigned int index = 0; index < instance.plugin()->port_count(); ++index)
		{
			std::cout << "Port: " << instance.plugin()->port_name(index) << std::endl;
			if (instance.the_plugin->port_is_bounded_below(index))
			{
				std::cout << "  Lower bound: " << instance.port_lower_bound(index) << std::endl;
			}

			if (instance.the_plugin->port_is_bounded_above(index))
			{
				std::cout << "  Upper bound: " << instance.port_upper_bound(index) << std::endl;
			}
			
			if (instance.the_plugin->port_has_default(index))
			{
				std::cout << "  Default: " << instance.port_default(index) << std::endl;
			}
		}
		
		instance.activate();
		
		instance.deactivate();
	}
	
	catch(const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}


