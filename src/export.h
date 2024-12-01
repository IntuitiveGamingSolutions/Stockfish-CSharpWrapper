#ifndef EXPORT_H
#define EXPORT_H
	#ifdef BUILD_DLL
		#ifdef _WIN32
			// For Windows
			#ifdef DLL_EXPORT
				#define DLL_API __declspec(dllexport)
			#else
				#define DLL_API __declspec(dllimport)
			#endif
		#elif defined(__APPLE__)
		  #define DLL_API __attribute__((visibility("default")))
		#else
			// For non-Windows platforms
			#define DLL_API
		#endif
	#else
		// For non-Windows platforms
		#define DLL_API
	#endif
#endif
