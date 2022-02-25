#pragma once

#ifdef OD_PLATFORM_WINDOWS

extern Odin::Application* Odin::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Odin::CreateApplication();
	app->Run();
	delete app;

}

#endif