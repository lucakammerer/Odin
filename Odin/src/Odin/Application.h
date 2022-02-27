#pragma once

#include "Core.h"

#include "Window.h"
#include "Odin/LayerStack.h"
#include "Odin/Events/Event.h"
#include "Odin/Events/ApplicationEvent.h"


namespace Odin {
	class ODIN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}



