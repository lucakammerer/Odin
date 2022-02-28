#include "odpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Odin/Application.h"

namespace Odin {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Odin key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_Z;

		ImGui_ImplGlfw_InitForOpenGL();
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui:GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImG(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(OD_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		return false;
	}
}