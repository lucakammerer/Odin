#pragma once

#include "Core.h"

#include "Window.h"
#include "Odin/LayerStack.h"
#include "Odin/Events/Event.h"
#include "Odin/Events/ApplicationEvent.h"

#include "Odin/ImGui/ImGuiLayer.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}