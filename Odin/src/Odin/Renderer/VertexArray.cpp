#include "odpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Odin {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		OD_CORE_ASSERT(false, "RendererAPI::None is currently not supported");  return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		OD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}