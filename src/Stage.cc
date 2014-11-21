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
	if (!_cam.init(w, h, 45.0f, glm::vec3{0, 10, 30}, glm::vec3{0, 10, 0}, glm::vec3{0, 1, 0})) return false;
	
	
	// Initialize scene
	if (!initScene()) return false;
	
	
	return true;
}

bool Stage::initScene() {
	
	Plane *left, *right, *top, *btm, *back, *front;
	
	left = new Plane{glm::vec3(1, 0, 0), glm::vec3(-10, 0, 0)};
	left->material().diffuse(0.7f, glm::vec3{1.0f, 0.0f, 0.0f});
	_scene.addPrimitive(left);
	
	right = new Plane{glm::vec3(-1, 0, 0), glm::vec3(10, 0, 0)};
	right->material().diffuse(0.7f, glm::vec3{0.0f, 1.0f, 0.0f});
	_scene.addPrimitive(right);
	
	top = new Plane{glm::vec3(0, -1, 0), glm::vec3(0, 20, 0)};
	top->material().diffuse(0.7f, glm::vec3{1.0f});
	_scene.addPrimitive(top);
	
	btm = new Plane{glm::vec3(0, 1, 0), glm::vec3(0, 0, 0)};
	btm->material().diffuse(0.7f, glm::vec3{1.0f});
	_scene.addPrimitive(btm);
	
	back = new Plane{glm::vec3(0, 0, 1), glm::vec3(0, 0, -10)};
	back->material().diffuse(0.7f, glm::vec3{1.0f});
	_scene.addPrimitive(back);
	
	front = new Plane{glm::vec3(0, 0, -1), glm::vec3(0, 0, 35)};
	front->material().diffuse(1.0f, glm::vec3{0.0f});
	_scene.addPrimitive(front);
	
	
	Sphere* light1 = new Sphere{glm::vec3(0, 15, 5), 0.2f};
	light1->light(true);
	light1->material().diffuse(0.6f, glm::vec3{1.0f, 1.0f, 1.0f});
	_scene.addPrimitive(light1);
	
	Sphere* light2 = new Sphere{glm::vec3(0, 15, 20), 0.2f};
	light2->light(true);
	light2->material().diffuse(0.6f, glm::vec3{1.0f, 1.0f, 1.0f});
	_scene.addPrimitive(light2);
	
	
	Sphere* s1 = new Sphere{glm::vec3(-1, 10, 0), 0.5f};
	s1->material().diffuse(0.8f, glm::vec3{0, 1, 0});
	s1->material().specular(0.8f, 50, glm::vec3(1.0));
	_scene.addPrimitive(s1);
	
	Sphere* s2 = new Sphere{glm::vec3(1, 10, 0), 0.5f};
	s2->material().diffuse(0.8f, glm::vec3{0, 1, 0});
	s2->material().specular(0.8f, 50, glm::vec3(1.0));
	_scene.addPrimitive(s2);
	
	Sphere* s3 = new Sphere{glm::vec3(1, 8, 0), 0.5f};
	s3->material().diffuse(0.8f, glm::vec3{0, 1, 0});
	s3->material().specular(0.8f, 50, glm::vec3(1.0));
	_scene.addPrimitive(s3);
	
	Sphere* s4 = new Sphere{glm::vec3(-1, 8, 0), 0.5f};
	s4->material().diffuse(0.8f, glm::vec3{0, 1, 0});
	s4->material().specular(0.8f, 50, glm::vec3(1.0));
	_scene.addPrimitive(s4);
	
	Sphere* big = new Sphere{glm::vec3(0, 9, 10), 2.0f};
	big->material().diffuse(1.0f, {1.0f, 0.0f, 0.0f});
	big->material().refraction(1.0f, 1.5f);
	big->material().specular(0.8f, 500, glm::vec3(1.0));
	_scene.addPrimitive(big);
	
	/*
	Sphere* s1 = new Sphere{glm::vec3(-1.2, 1, 0), 1.0f};
	s1->material().diffuse(1.0f, glm::vec3{1, 1, 0});
	s1->material().specular(0.8f, 10, glm::vec3(1.0));
	s1->material().reflection(0.4f);
	_scene.addPrimitive(s1);
	
	Sphere* s2 = new Sphere{glm::vec3(1.2, 1, 0), 1.0f};
	s2->material().diffuse(1.0f, glm::vec3{0, 1, 1});
	s2->material().specular(0.9f, 50, glm::vec3(1.0));
	s2->material().reflection(0.4f);
	_scene.addPrimitive(s2);
	
	Sphere* s3 = new Sphere{glm::vec3(0, 1, -2), 1.0f};
	s3->material().diffuse(1.0f, glm::vec3{1, 0, 1});
	s3->material().specular(0.9f, 50, glm::vec3(1.0));
	s3->material().reflection(0.4f);
	_scene.addPrimitive(s3);
	
	
	Sphere* s4 = new Sphere{glm::vec3(0, 1, 8), 1.0f};
	s4->material().diffuse(1.0f, glm::vec3{1, 1, 1});
	s4->material().specular(0.9f, 50, glm::vec3(1.0));
	s4->material().refraction(1.0f, 1.5f);
	_scene.addPrimitive(s4);
	
	
	Plane* p1 = new Plane{glm::vec3(0, 1, 0), glm::vec3(0, -2, 0)};
	p1->material().diffuse(0.7f, glm::vec3{1.0f});
	p1->material().reflection(0.2f);
	_scene.addPrimitive(p1);
	
	Plane* p2 = new Plane{glm::vec3(0, 0, 1), glm::vec3(0, 0, -10)};
	p2->material().diffuse(0.7f, glm::vec3{1.0f, 0.0f, 0.0f});
	_scene.addPrimitive(p2);
	
	Sphere* light1 = new Sphere{glm::vec3(10, 10, 20), 0.2f};
	light1->light(true);
	light1->material().diffuse(1.0f, glm::vec3{1.0f, 1.0f, 1.0f});
	_scene.addPrimitive(light1);
	
	Sphere* light2 = new Sphere{glm::vec3(-10, 10, -20), 0.2f};
	light2->light(true);
	light2->material().diffuse(1.0f, glm::vec3{1.0f, 1.0f, 1.0f});
	_scene.addPrimitive(light2);
	*/
	
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
			uint32_t start = SDL_GetTicks();
			_rayTracer.render(_scene, _cam);
			Texture::updateTexture(_resultTex, _rayTracer.resultData());
			start = SDL_GetTicks() - start;
			printf("Rendered in %fs\n", start / 1000.0f);
		}
	}
}