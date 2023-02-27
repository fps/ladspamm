#include <ladspamm1/world.h>
#include <ladspamm1/library.h>
#include <ladspamm1/plugin.h>
#include <ladspamm1/plugin_instance.h>

#include <iostream>
#include <vector>

int main()
{
	using namespace ladspamm1;

	library l("/usr/lib/ladspa/ladspa.m.osc.plugins1.so");
	plugin_instance i(l.plugins[0], 1000);

	std::vector<float> freq(1000, 1);
	std::vector<float> phase(1000, 0);
	std::vector<float> trigger(1000, 0);
	std::vector<float> out(1000, 0);

	i.connect_port(0, &freq[0]);
	i.connect_port(1, &phase[0]);
	i.connect_port(2, &trigger[0]);
	i.connect_port(3, &out[0]);

	i.run(1000);

	for (size_t frame = 0; frame < 1000; ++frame)
	{
		std::cout << out[frame] << std::endl;
	}	
}

