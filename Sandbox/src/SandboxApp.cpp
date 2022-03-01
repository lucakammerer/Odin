#include <Odin.h>

#include "imgui/imgui.h"

class ExampleLayer : public Odin::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Odin::Input::IsKeyPressed(OD_KEY_TAB))
			OD_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Odin::Event& event) override
	{
		if (event.GetEventType() == Odin::EventType::KeyPressed)
		{
			Odin::KeyPressedEvent& e = (Odin::KeyPressedEvent&)event;
			if (e.GetKeyCode() == OD_KEY_TAB)
				OD_TRACE("Tab key is pressed (event)!");
			OD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Odin::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Odin::Application* Odin::CreateApplication()
{
	return new Sandbox();
}