#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <dlfcn.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace ladspamm
{
	/**
	* @brief A utility type just to get a reference counted
	* dlopen() handle..
	*/
	struct dl : boost::noncopyable 
	{
		void *dl_handle;
		std::string filename;
		
		dl(std::string filename, int flags = RTLD_NOW)
		throw 
		(
			std::runtime_error
		)
		:
			filename(filename)
		{
			/**
			* Reset possible leftover errors.
			*/
			dlerror();
			
			dl_handle = dlopen(filename.c_str(), flags);
			
			if (NULL == dl_handle)
			{
				throw std::runtime_error("Failed to dlopen " + filename + " Reason: " + dlerror());
			}
		}
		
		~dl() 
		{
			dlclose(dl_handle);
		}
	};
	
	typedef boost::shared_ptr<dl> dl_ptr;
} // namespace
	
#endif