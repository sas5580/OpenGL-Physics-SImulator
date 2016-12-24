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
Camera camera(glm::vec3(0.0f, 0.0f, 4.0f), 70.0f, display.getAspectRatio(), 0.01f, 1000.0f);
Transform transform;

int main(int argc, char *args[])
{
	SDL_Event e;
	bool isRunning = true;

	PhysicsObject(&monkey, &texture);
	
	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				isRunning = false;
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
