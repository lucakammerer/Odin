#pragma once

#ifdef OD_PLATFORM_WINDOWS

extern Odin::Application* Odin::CreateApplication();

int main(int argc, char** argv)
{
	Odin::Log::Init();
	OD_CORE_WARN("Initialized Log!");
	int a = 5;
	OD_CORE_INFO("Hello! Var={0}", a);

	auto app = Odin::CreateApplication();
	app->Run();
	delete app;

}

#endif