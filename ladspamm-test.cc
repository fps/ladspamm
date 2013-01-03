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
		
		std::cout << "Name: " << instance.the_plugin->name() << std::endl;
		
		for (unsigned int index = 0; index < instance.the_plugin->port_count(); ++index)
		{
			std::cout << "Port: " << instance.the_plugin->port_name(index) << std::endl;
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


