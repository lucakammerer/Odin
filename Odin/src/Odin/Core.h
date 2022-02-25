#pragma once

#ifdef OD_PLATFORM_WINDOWS
	#ifdef OD_BUILD_DLL
		#define ODIN_API __declspec(dllexport)
	#else
		#define ODIN_API __declspec(dllimport)
	#endif
#else
	#error Odin only supports Windows!
#endif