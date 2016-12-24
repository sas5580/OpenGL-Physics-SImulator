#include "physicsobject.h"

glm::vec3 PhysicsObject::gravity = glm::vec3();
std::vector <PhysicsObject*> PhysicsObject::AllObjects;

PhysicsObject::PhysicsObject(Mesh* mesh, Texture* texture, glm::vec3 pos, glm::vec3 vel, glm::vec3 acc )
{
	m_mesh = mesh;
	m_texture = texture;

	m_pos = pos;
	m_vel = vel;
	m_acc = acc;

	AllObjects.push_back(this);
}

void PhysicsObject::Update()
{
	for (unsigned int i = 0; i < AllObjects.size(); i++)
	{
		PhysicsObject* obj = AllObjects[i];

		obj->m_vel += obj->m_acc + gravity;
		obj->m_pos += obj->m_vel;

		obj->m_transform.SetPos(obj->m_pos);
	}
}

void PhysicsObject::Render(Shader* shader, Camera* camera)
{
	for (unsigned int i = 0; i < AllObjects.size(); i++)
	{
		PhysicsObject* obj = AllObjects[i];

		shader->Update(obj->m_transform, *camera);
		obj->m_texture->Bind();

		obj->m_mesh->Draw();
	}
}
