#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	
	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline float getAspectRatio() { return m_aspectRatio; }

	virtual ~Display();
protected:
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	int m_width;
	int m_height;
	float m_aspectRatio;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

#endif // DISPLAY_H