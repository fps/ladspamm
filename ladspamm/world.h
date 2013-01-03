#ifndef LADSPAPP_LADSPA_WORLD_HH
#define LADSPAPP_LADSPA_WORLD_HH

#include <string>
#include <vector>

#include <ladspamm-VERSION/ladspamm.h>

namespace ladspamm 
{
	struct world
	{	
		const std::vector<ladspamm::library_ptr> libraries;
		
		world(std::string path = get_path_from_environment())
		throw 
		(
			std::runtime_error
		)
		:
			libraries(ladspamm::world_scan(path))
		{
			
		}
	};
} // namespace

#endif
