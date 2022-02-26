#include "odpch.h"
#include "Application.h"

#include "Odin/Events/ApplicationEvent.h"
#include "Odin/Log.h"

namespace Odin {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}