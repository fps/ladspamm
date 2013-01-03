#include <ladspamm-0/world.h>
#include <ladspamm-0/plugin_instance.h>

int main() 
{
	ladspamm::world world;
	
	ladspamm::plugin_instance_ptr instance
	(
		new ladspamm::plugin_instance(world.libraries[0]->plugins[0], 48000)
	);
	
	instance->activate();
	
	instance->deactivate();
}


