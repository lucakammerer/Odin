#include <Odin.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Odin::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Odin::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Odin::Ref<Odin::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Odin::VertexBuffer::Create(vertices, sizeof(vertices)));
		Odin::BufferLayout layout = {
			{ Odin::ShaderDataType::Float3, "a_Position" },
			{ Odin::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Odin::Ref<Odin::IndexBuffer> indexBuffer;
		indexBuffer.reset(Odin::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Odin::VertexArray::Create());
		
		float squareVertices[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,
		    0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
		};

		Odin::Ref<Odin::VertexBuffer> squareVB;
		squareVB.reset(Odin::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Odin::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Odin::Ref<Odin::IndexBuffer> squareIB;
		squareIB.reset(Odin::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Odin::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Odin::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));
	}

	void OnUpdate(Odin::Timestep ts) override
	{
		if (Odin::Input::IsKeyPressed(OD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Odin::Input::IsKeyPressed(OD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Odin::Input::IsKeyPressed(OD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Odin::Input::IsKeyPressed(OD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Odin::Input::IsKeyPressed(OD_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Odin::Input::IsKeyPressed(OD_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Odin::RenderCommand::SetClearColor({ 0.1f, 0.05f, 0.1f, 1 });
		Odin::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Odin::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Odin::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Odin::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Odin::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		Odin::Renderer::Submit(m_Shader, m_VertexArray);

		Odin::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Odin::Event& event) override
	{
		Odin::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Odin::KeyPressedEvent>(OD_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Odin::KeyPressedEvent& event)
	{
		return false;
	}
private:
	Odin::Ref<Odin::Shader> m_Shader;
	Odin::Ref<Odin::VertexArray> m_VertexArray;

	Odin::Ref<Odin::Shader> m_FlatColorShader;
	Odin::Ref<Odin::VertexArray> m_SquareVA;

	Odin::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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