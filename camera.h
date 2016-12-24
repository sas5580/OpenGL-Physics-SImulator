#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar,
		glm::vec3  forward = glm::vec3(0, 0, -1))
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::normalize(forward);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position+m_forward, m_up);
	}

	glm::vec3* GetPos() { return &m_position; }
	glm::vec3* GetForwardDir() { return &m_forward; }

	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetForwardDir(const glm::vec3& dir) { m_up = glm::normalize(dir); }

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif //CAMERA_H_INCLUDED