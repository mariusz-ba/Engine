#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include "../utilities/Utils.h"


namespace engine { namespace graphics {

	class Shader
	{
	public:
		Shader(std::string vertex_path, std::string fragment_path);
		~Shader();

		void enable();
		void disable();

		// set uniforms, get uniforms etc..
		
		void setUniform1i(const GLchar* name, GLint value);
		void setUnifrom1iv(const GLchar* name, GLint* values, GLint count);
		void setUniform2f(const GLchar* name, const glm::vec2& vec);
		void setUniform4f(const GLchar* name, const glm::vec4& vec);
		void setUniformMat4(const GLchar* name, const glm::mat4& mat);

		GLuint getUniformLocation(const GLchar* name);

	private:
		GLuint load();

	private:
		GLuint m_Program;
		std::string m_VertexPath;
		std::string m_FragmentPath;

		std::map<const GLchar*, GLuint> m_UniformLocations;
	};

} }


