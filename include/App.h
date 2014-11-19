#ifndef __App_H__
#define __App_H__

#include "Display.h"

class App {
private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	
	int _resX, _resY;
	bool _done = false;
	
	Display _result;
	
	
	void initGL();
	
public:
	App();
	~App();
	
	bool init(const char* title, int width, int height);
	void release();
	
	void handleEvents();
	void update();
	void render();
	
	
	bool done() const { return _done; }
	SDL_Window* window() { return _window; }
	SDL_GLContext& context() { return _glContext; }
	
	
	int resX() const { return _resX; }
	int resY() const { return _resY; }
	
	static App*& getInstance();
};


#endif
