#include <ladspamm-0/world.h>
#include <ladspamm-0/plugin_instance.h>

#include <iostream>
#include <cstdlib>

int main() 
{
	try
	{
		ladspamm::world world;
		
		
		for (unsigned int lib_index = 0; lib_index < world.libraries.size(); ++ lib_index)
		{
			std::cout << "Library: " << world.libraries[lib_index]->the_dl->filename << std::endl;
			
			for (unsigned int plugin_index = 0; plugin_index < world.libraries[lib_index]->plugins.size(); ++plugin_index)
			{
				ladspamm::plugin_instance instance(world.libraries[lib_index]->plugins[plugin_index], 48000);
				
				std::cout << "  Name: " << instance.plugin()->name() << std::endl;

				for (unsigned int port_index = 0; port_index < instance.plugin()->port_count(); ++port_index)
				{
					std::cout << "    Port: " << instance.plugin()->port_name(port_index) << std::endl;
					if (instance.the_plugin->port_is_bounded_below(port_index))
					{
						std::cout << "      Lower bound: " << instance.port_lower_bound(port_index) << std::endl;
					}

					if (instance.the_plugin->port_is_bounded_above(port_index))
					{
						std::cout << "      Upper bound: " << instance.port_upper_bound(port_index) << std::endl;
					}
					
					if (instance.the_plugin->port_has_default(port_index))
					{
						std::cout << "      Default: " << instance.port_default_guessed(port_index) << std::endl;
					}
				}
				
				instance.activate();
				instance.deactivate();
			}
		}
	}
	
	catch(const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}


