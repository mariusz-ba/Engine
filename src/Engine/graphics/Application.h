#pragma once

#include "Window.h"
#include <chrono>

namespace engine {

	using namespace graphics;

	class Application {
	public:
		Application(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight);
		virtual ~Application();

		virtual void Run();

	protected:
		virtual void OnInit();
		virtual void OnEvent();
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();

	protected:
		Window m_Window;
	};

}