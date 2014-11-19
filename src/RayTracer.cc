#include "RayTracer.h"


Ray::Ray() : _origin(glm::vec3(0)), _direction(glm::vec3(0)) {}

Ray::Ray(glm::vec3& origin, glm::vec3& direction) : _origin(origin), _direction(direction) {}



// Raytracer definitions
bool RayTracer::init(GLuint width, GLuint height) {
	if (width == 0 || height == 0) return false;
	_width = width;
	_height = height;
	
	
	const int dataSize = _width * _height * 3;
	_resultData = new GLubyte[dataSize];
	
	
	return true;
}

void RayTracer::release() {
	if (_resultData) delete[] _resultData;
}


void RayTracer::render(const Scene& scene) {
	for (int i = 0; i < _width * _height * 3; i += 3) {
		_resultData[i + 0] = rand() % 255;
		_resultData[i + 1] = rand() % 255;
		_resultData[i + 2] = rand() % 255;
	}
}