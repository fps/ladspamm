#ifndef LADSPAPP_LADSPA_WORLD_HH
#define LADSPAPP_LADSPA_WORLD_HH

#include <string>
#include <vector>
#include <boost/regex.hpp>

#include <ladspamm/ladspamm.h>
#include <ladspamm/plugin.h>

namespace ladspamm 
{
	struct world
	{
		const std::vector<ladspamm::library_ptr> libraries;
		
		world(std::string path = get_path_from_environment())
		:
			libraries(ladspamm::world_scan(path))
		{
			
		}
		
		std::vector<plugin_ptr> find_plugins_by_name(std::string name_regex)
		{
			return std::vector<plugin_ptr>();
		}
		
		std::vector<plugin_ptr> find_plugins_by_label(std::string label_regex)
		{
			return std::vector<plugin_ptr>();
		}
		
		plugin_ptr find_plugin_by_uid(unsigned long uid)
		{
			for (unsigned int library_index = 0; library_index < libraries.size(); ++library_index)
			{
				for (unsigned int plugin_index = 0; plugin_index < libraries[library_index]->plugins.size(); ++plugin_index)
				{
					if (libraries[library_index]->plugins[plugin_index]->uid() == uid)
					{
						return libraries[library_index]->plugins[plugin_index];
					}
				}
			}
			return plugin_ptr();
		}
	};
} // namespace

#endif
