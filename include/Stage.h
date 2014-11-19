#ifndef __STAGE_H__
#define __STAGE_H__

#include "Surface.h"
#include "Texture.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Camera.h"

class Stage {
protected:
	Camera _cam;
	Scene _scene;
	RayTracer _rayTracer;
	
	TexData _resultTex;
	Surface _result;
	
	bool initScene();
	
public:
	bool init();
	void update();
	void render();
	void release();
	
	void handleEvents(const SDL_Event& e);
};

#endif