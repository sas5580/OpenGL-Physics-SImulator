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

int main(int argc, char *args[])
{
	Display display(WIDTH, HEIGHT, "Hello World!");

	Vertex verticies[] = {  Vertex(glm::vec3(-0.5, -0.5,  0.0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 1)),
							Vertex(glm::vec3( 0.0,  0.5,  0.0), glm::vec2(0.5, 1.0), glm::vec3(0, 0, 1)),
							Vertex(glm::vec3( 0.5, -0.5,  0.0), glm::vec2(1.0, 0.0), glm::vec3(0, 0, 1)), };

	unsigned int indicies[] = { 0, 1, 2 };

	Mesh triangle(verticies, sizeof(verticies) / sizeof(verticies[0]), indicies, sizeof(indicies) / sizeof(indicies[0]));
	Mesh monkey(".\\res\\monkey3.obj");
	Mesh sphere(".\\res\\sphere.obj");
	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\bricks.jpg");
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 70.0f, display.getAspectRatio(), 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		//transform.getPos().z += 1e-4;
		//transform.getPos().z = 0.5f * cosf(counter);
		//transform.getRot().x = counter;
		transform.GetRot()->y = counter;
		//transform.getRot().z = counter;
		//transform.getScale().x = sinf(counter) + 1.5f;
		//transform.getScale().y = sinf(counter) + 1.5f;
		
		shader.Bind();
		shader.Update(transform, camera);

		texture.Bind();

		monkey.Draw();

		display.Update();

		counter += 0.0002f;
	}

	return 0;
}
