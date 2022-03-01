#pragma once

#include "Odin/Layer.h"

#include "Odin/Events/ApplicationEvent.h"
#include "Odin/Events/KeyEvent.h"
#include "Odin/Events/MouseEvent.h"

namespace Odin {

	class ODIN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}