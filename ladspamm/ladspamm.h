#ifndef LADSPA_WORLD_HH
#define LADSPA_WORLD_HH

#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <library.h>
#include <ladspa/library.h>

namespace ladspamm 
{

	inline std::string get_ladspa_path_from_environment(std::string environment_variable_name = "LADSPA_PATH")
	throw 
	(
		std::runtime_error
	)
	{
		char *path = getenv(environment_variable_name.c_str());
		
		if (NULL == path) 
		{
			throw std::runtime_error("Enironment variable " + environment_variable_name + " not found in environment");
		}
		
		return std::string(path);
	}

	/**
	 * Splits a path string at the separators and returns a vector<string> with
	 * the components..
	 */
	inline std::vector<std::string> split_path(std::string path, char separator) 
	{
		std::vector<std::string> components;
		std::stringstream stream(path);
		
		std::string component;
		while(std::getline(stream, component, separator))
		{
			components.push_back(component);
		}
		
		return components;
	}

	/**
	 * If load_libraries is false, then the ladspa_library objects
	 * returned in the collection need to be loaded manually.
	 * 
	 * This is useful to avoid crashing libraries. On the other
	 * hand there might be race conditions with library files going 
	 * away after scanning. Then the ladspa_library load() function
	 * will fail with an exception.
	 * 
	 * Note that with load_libraries == false there is no check
	 * for the found files in the ladspa_path are actually ladspa 
	 * library files.. 
	 */
	inline std::vector<ladspa_library_ptr> ladspa_world_scan
	(
		std::string ladspa_path
	)
	throw 
	(
		std::runtime_error
	)
	{
		std::vector<std::string> ladspa_path_components = split_path(ladspa_path, ':');
	
		std::vector<ladspa_library_ptr> libraries;
		
		try
		{
			for (unsigned int index = 0; index < ladspa_path_components.size(); ++index) 
			{
				std::cerr << "LADSPA_PATH component: " << ladspa_path_components[index] << std::endl;
				
				boost::filesystem::path path(ladspa_path_components[index]);
				
				if (false == boost::filesystem::is_directory(path))
				{
					continue;
				}
				
				for 
				(
					boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(path);
					it != boost::filesystem::directory_iterator();
					++it
				)
				{
					std::cerr << "LADSPA library: " << (*it).path().c_str() << std::endl;
					try
					{
						library_ptr the_library(new library((*it).path().c_str()));
						libraries.push_back(ladspa_library_ptr(new ladspa_library(the_library)));
					}
					catch (std::runtime_error e) 
					{
						std::cerr << "Warning: could not load library: " << (*it).path().c_str() << " " << e.what() << std::endl;
					}
				}
			}
		}
		catch (boost::filesystem::filesystem_error e) 
		{
			throw std::runtime_error(e.what());
		}
		
		return libraries;
	}
} // namespace

#endif
