#include "odpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Odin {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}