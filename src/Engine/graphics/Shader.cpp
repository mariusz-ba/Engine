#include "Shader.h"

namespace engine { namespace graphics {

	Shader::Shader(std::string vertex_path, std::string fragment_path)
		: m_VertexPath(vertex_path), m_FragmentPath(fragment_path)
	{
		m_Program = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}

	void Shader::enable()
	{
		glUseProgram(m_Program);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	GLuint Shader::load()
	{
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint program = glCreateProgram();

		std::string vertexSourceString = read_file(m_VertexPath);
		std::string fragmentSourceString = read_file(m_FragmentPath);

		const char* vertex_source = vertexSourceString.c_str();
		const char* fragment_source = fragmentSourceString.c_str();

		glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
		glShaderSource(fragment_shader, 1, &fragment_source, nullptr);

		GLint compilation_result;
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compilation_result);
		if (compilation_result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex_shader, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader:\n" << &error[0] << std::endl;
			glDeleteShader(vertex_shader);
			return 0;
		}

		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compilation_result);
		if (compilation_result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment_shader, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader:\n" << &error[0] << std::endl;
			glDeleteShader(fragment_shader);
			return 0;
		}

		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		std::cout << "Shaders successfully compiled" << std::endl;
		return program;
	}

	void Shader::setUniform1i(const GLchar * name, GLint value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUnifrom1iv(const GLchar * name, GLint * values, GLint count)
	{
		glUniform1iv(getUniformLocation(name), count, values);
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vec)
	{
		glUniform2fv(getUniformLocation(name), 1, &vec[0]);
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vec)
	{
		glUniform4fv(getUniformLocation(name), 1, &vec[0]);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
	}

	GLuint Shader::getUniformLocation(const GLchar* name)
	{
		if (m_UniformLocations.count(name))
			return m_UniformLocations[name];

		m_UniformLocations[name] = glGetUniformLocation(m_Program, name);
		return m_UniformLocations[name];
	}

} }