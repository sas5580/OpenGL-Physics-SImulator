#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include "transform.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class PhysicsObject
{
public:
	PhysicsObject(Mesh* mesh, Texture* texture, glm::vec3 pos, glm::vec3 vel, glm::vec3 acc);

	static void SetGravity(glm::vec3 g) { gravity = g; }

	static std::vector <PhysicsObject*> AllObjects;

	static void Update();
	static void Render(Shader* shader, Camera* camera);
	

protected:
private:
	static glm::vec3 gravity;

	glm::vec3 m_pos;
	glm::vec3 m_vel;
	glm::vec3 m_acc;

	Mesh* m_mesh;
	Texture* m_texture;
	Transform m_transform;
};

#endif // !PHYSICSOBJECT_H



