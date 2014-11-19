#include "Display.h"
#include "App.h"
#include "Shader.h"
#include "ShaderSrc.h"



bool Display::init() {
	auto app = App::getInstance();
	const int w = app->resX();
	const int h = app->resY();
	
	
	// Init raytracer
	if (!_rayTracer.init(w, h)) return false;
	
	
	// Create texture holding the result
	_resultTex.width = w;
	_resultTex.height = h;
	_resultTex.format = GL_RGB;
	if (!Texture::createTexture(_resultTex, _rayTracer.resultData())) return false;
	
	// Create result surface
	if (!_result.init(_resultTex.id, w, h)) return false;
	
	
	// Initialize scene
	Sphere* s = new Sphere{glm::vec3(0), 1.0f};
	_scene.addPrimitive(s);
	if (!_scene.init()) return false;
	
	
	return true;
}

void Display::release() {
	_rayTracer.release();
	_result.release();
	_scene.release();
}

void Display::update() {
	
}

void Display::render() {
	_result.render();
}

void Display::handleEvents(const SDL_Event& e) {
	if (e.type == SDL_KEYDOWN || e.key.state == SDL_PRESSED) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			_rayTracer.render(_scene);
			Texture::updateTexture(_resultTex, _rayTracer.resultData());
		}
	}
}