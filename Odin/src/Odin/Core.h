#pragma once

#ifdef OD_PLATFORM_WINDOWS
#if OD_DYNAMIC_LINK
	#ifdef OD_BUILD_DLL
		#define ODIN_API __declspec(dllexport)
	#else
		#define ODIN_API __declspec(dllimport)
	#endif
#else
	#define ODIN_API
#endif
#else
	#error Odin only supports Windows!
#endif

#ifdef OD_DEBUG
	#define OD_ENABLE_ASSERTS
#endif

#if OD_ENABLE_ASSERT
	#define OD_ASSERT(x, ...) { if(!(x)) { OD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define OD_CORE_ASSERT(x, ...) { if(!(x)) { OD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define OD_ASSERT(x, ...)
	#define OD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define OD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)