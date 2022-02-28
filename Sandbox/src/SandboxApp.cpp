#include "odpch.h"
#include <Odin.h>

class ExampleLayer : public Odin::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		OD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Odin::Event& event) override
	{
		OD_TRACE("{0}", event);
	}
};

class Sandbox : public Odin::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Odin::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Odin::Application* Odin::CreateApplication()
{
	return new Sandbox();
}