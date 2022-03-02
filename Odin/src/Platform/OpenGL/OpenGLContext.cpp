#include "odpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Odin {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		OD_CORE_ASSERT(windowHandle, "Window Handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OD_CORE_ASSERT(status, "Failed to initialize Glad!");

		OD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		OD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		OD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{

		glfwSwapBuffers(m_WindowHandle);
	}


}