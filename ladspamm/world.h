#ifndef LADSPAPP_LADSPA_WORLD_HH
#define LADSPAPP_LADSPA_WORLD_HH

#include <string>
#include <vector>

#include <ladspamm-VERSION/ladspamm.h>

namespace ladspamm 
{
	/**
	 * @brief This class represents the world of LADSPA plugins.
	 */
	struct world
	{	
		/**
		 * @brief The libraries found in the system.
		 */
		const std::vector<ladspamm::library_ptr> libraries;
		
		/**
		 * @brief This constructor scans the system (parsing LADSPA_PATH or
		 * using sensible defaults).
		 */
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
