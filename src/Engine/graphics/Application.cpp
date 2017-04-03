#include "Application.h"

namespace engine {

	Application::Application(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight)
		: m_Window(windowTitle, windowWidth, windowHeight)
	{
		// Construct an application
		OnInit();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		using namespace std;
		using namespace chrono;

		steady_clock::time_point start = steady_clock::now();
		float frameRate = 1.0 / 60;

		while (m_Window.isOpen())
		{
			// Catch events
			OnEvent();

			steady_clock::time_point current = steady_clock::now();
			float duration = duration_cast<milliseconds>(current - start).count() / 1000.f;

			while (duration >= frameRate)
			{
				// Update and render
				OnUpdate(duration);
				OnRender();

				duration -= frameRate;
				start = current;
			}
		}
	}

	//! \brief Initialise everything (like shaders etc.)
	void Application::OnInit()
	{

	}

	void Application::OnEvent()
	{

	}

	void Application::OnUpdate(float deltaTime)
	{
		
	}

	void Application::OnRender()
	{
		m_Window.clear();

		m_Window.update();
	}

}