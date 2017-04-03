#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

namespace engine { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

	class Window {
	public:
		Window(const std::string& title, unsigned int width, unsigned int height);
		~Window();

		void clear() const;
		void update();
		inline void close() { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

		inline std::string getTitle() const { return m_Title; }
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline bool isOpen() const { return glfwWindowShouldClose(m_Window) == 0; };

		void setSize(unsigned int width, unsigned int height);

		bool isKeyPressed(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int buttoncode) const;
		inline glm::vec2 getCursorPosition() const { return glm::vec2(m_MouseX, m_MouseY); }
	private:
		bool init();
		friend static void resize_callback(GLFWwindow* window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	private:
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
		GLFWwindow* m_Window;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double m_MouseX;
		double m_MouseY;
	};

} }