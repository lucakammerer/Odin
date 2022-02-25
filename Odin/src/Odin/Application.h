#pragma once

#include "Core.h"

namespace Odin {
	class ODIN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}



