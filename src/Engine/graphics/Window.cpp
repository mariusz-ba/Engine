#include "Window.h"

namespace engine { namespace graphics {

	Window::Window(const std::string& title, unsigned int width, unsigned int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		if (!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; ++i)
			m_Keys[i] = false;

		for (int i = 0; i < MAX_BUTTONS; ++i)
			m_MouseButtons[i] = false;
	}

	Window::~Window()
	{
		glfwTerminate();
	}
	
	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 8);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		
		// Setup callbacks
		glfwSetWindowSizeCallback(m_Window, resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);


		// Setup GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL error: " << error << std::endl;
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::setSize(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
		glViewport(0, 0, width, height);
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int buttoncode) const
	{
		if (buttoncode >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[buttoncode];
	}

	void resize_callback(GLFWwindow* window, int width, int height)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->setSize(width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_MouseX = xpos;
		win->m_MouseY = ypos;
	}

} }