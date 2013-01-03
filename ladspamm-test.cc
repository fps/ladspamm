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


