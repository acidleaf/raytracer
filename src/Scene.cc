#include "Scene.h"

bool Scene::init() {
	
	return true;
}

void Scene::release() {
	for (auto i = _primitives.begin(); i != _primitives.end(); ++i) {
		delete (*i);
	}
}

void Scene::addPrimitive(Primitive* p) {
	_primitives.push_back(p);
}