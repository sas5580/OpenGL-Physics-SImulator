#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "GL/glew.h"
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& fileName, glm::vec3 LightDir = glm::vec3(0.0f, 0.0f, -1.0f));

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();

	glm::vec3* GetLightDir() { return &m_LightDirection; }

protected:
private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		MVP_U,
		NORMAL_U,
		LIGHTDIRECTION_U,
		NUM_UNIFORMS
	};

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	glm::vec3 m_LightDirection;
};


#endif // !SHADER_H
