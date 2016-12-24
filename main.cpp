#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "physicsobject.h"

#define WIDTH 800
#define HEIGHT 600

Display display(WIDTH, HEIGHT, "Hello World!");

Vertex verticies[] = { Vertex(glm::vec3(-0.5, -0.5,  0.0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 1)),
Vertex(glm::vec3(0.0,  0.5,  0.0), glm::vec2(0.5, 1.0), glm::vec3(0, 0, 1)),
Vertex(glm::vec3(0.5, -0.5,  0.0), glm::vec2(1.0, 0.0), glm::vec3(0, 0, 1)), };

unsigned int indicies[] = { 0, 1, 2 };

Mesh triangle(verticies, sizeof(verticies) / sizeof(verticies[0]), indicies, sizeof(indicies) / sizeof(indicies[0]));
Mesh monkey(".\\res\\monkey3.obj");
Mesh sphere(".\\res\\sphere.obj");
Shader shader(".\\res\\basicShader");
Texture texture(".\\res\\bricks.jpg");
Camera camera(glm::vec3(0.0f, 2.0f, 8.0f), 70.0f, display.getAspectRatio(), 0.01f, 1000.0f,
	glm::vec3(0.0f, -2.0f, -4.0f));
Transform transform;

int main(int argc, char *args[])
{
	SDL_Event e;
	bool isRunning = true;

	PhysicsObject monkey1 = PhysicsObject(&monkey, &texture);
	//PhysicsObject monkey2 = PhysicsObject(&monkey, &texture, glm::vec3(-2.0f, 2.0f, 0.0f));

	PhysicsObject::SetGravity(glm::vec3(0.0f, -5e-6f, 0.0f));
	
	while (isRunning)
	{
		//controls
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYUP:
				if (PhysicsObject::GetNumObjects())
				{
					unsigned int curObj = PhysicsObject::GetNumObjects() - 1;
					switch (e.key.keysym.sym)
					{
					case SDLK_SPACE:
						PhysicsObject::AllObjects[curObj]->SetHanging(false);
						break;

					case SDLK_LEFT: case SDLK_RIGHT:
						PhysicsObject::AllObjects[curObj]->GetVel()->x = 0;
						break;
					}
				}
				break;

			case SDL_KEYDOWN:
				if (PhysicsObject::GetNumObjects())
				{
					unsigned int curObj = PhysicsObject::GetNumObjects() - 1;
					switch (e.key.keysym.sym)
					{
					case SDLK_LEFT:
						PhysicsObject::AllObjects[curObj]->GetVel()->x = -0.003f;
						break;

					case SDLK_RIGHT:
						PhysicsObject::AllObjects[curObj]->GetVel()->x = 0.003f;
						break;
					}
				}
			}
		}

		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		shader.Bind();

		PhysicsObject::Update();
		PhysicsObject::Render(&shader, &camera);

		display.SwapBuffers();
		SDL_Delay(1);
	}

	return 0;
}
