#include "Stage.h"
#include "App.h"
#include "Shader.h"
#include "ShaderSrc.h"



bool Stage::init() {
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
	
	
	// Initialize camera
	if (!_cam.init(w, h, 45, glm::vec3{0, 1, 10}, glm::vec3{0}, glm::vec3{0, 1, 0})) return false;
	
	
	// Initialize scene
	if (!initScene()) return false;
	
	
	return true;
}

bool Stage::initScene() {
	
	Sphere* s1 = new Sphere{glm::vec3(-3, 0, 0), 2.0f};
	s1->material().diffuse(0.5f, glm::vec3{1.0, 0.3, 0.3});
	_scene.addPrimitive(s1);
	
	Sphere* s2 = new Sphere{glm::vec3(0), 1.0f};
	s2->material().diffuse(0.5f, glm::vec3{0, 0.5, 0.3});
	_scene.addPrimitive(s2);
	
	Plane* p1 = new Plane{glm::vec3(0, 1, 0), 0.0f};
	p1->material().diffuse(1.0f, glm::vec3{0.2f, 0.9f, 0.9f});
	_scene.addPrimitive(p1);
	
	Sphere* light = new Sphere{glm::vec3(0, 2, 3), 0.5f};
	light->light(true);
	light->material().diffuse(1.0f, glm::vec3{1});
	_scene.addPrimitive(light);
	
	if (!_scene.init()) return false;
	
	return true;
}

void Stage::release() {
	_rayTracer.release();
	_result.release();
	_scene.release();
}

void Stage::update() {
	
}

void Stage::render() {
	_result.render();
}

void Stage::handleEvents(const SDL_Event& e) {
	if (e.type == SDL_KEYDOWN || e.key.state == SDL_PRESSED) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			_rayTracer.render(_scene, _cam);
			Texture::updateTexture(_resultTex, _rayTracer.resultData());
		}
	}
}