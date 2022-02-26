#include "odpch.h"
#include <Odin.h>

class Sandbox : public Odin::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Odin::Application* Odin::CreateApplication()
{
	return new Sandbox();
}