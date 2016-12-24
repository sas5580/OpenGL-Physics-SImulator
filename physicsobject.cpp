#include "physicsobject.h"

#include <iostream>

glm::vec3 PhysicsObject::gravity = glm::vec3();
std::vector <PhysicsObject*> PhysicsObject::AllObjects;
unsigned int PhysicsObject::NumObjects = 0;

PhysicsObject::PhysicsObject(Mesh* mesh, Texture* texture, glm::vec3 pos, glm::vec3 vel, glm::vec3 acc )
{
	m_mesh = mesh;
	m_texture = texture;

	m_pos = pos;
	m_vel = vel;
	m_acc = acc;

	m_hanging = true;

	NumObjects++;
	AllObjects.push_back(this);
}

void PhysicsObject::Update()
{
	for (unsigned int i = 0; i < AllObjects.size(); i++)
	{
		PhysicsObject* obj = AllObjects[i];

		if (obj->m_pos.y < -10.0f)
		{
			AllObjects.erase(AllObjects.begin() + i);
			NumObjects--;
			return;
		}

		obj->m_vel += obj->m_acc;
		obj->m_pos += obj->m_vel;

		if (!obj->m_hanging)
			obj->m_vel += gravity;

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
