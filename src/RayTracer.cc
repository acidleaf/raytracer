#include "RayTracer.h"
#include "Camera.h"
#include "Scene.h"

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

void RayTracer::setPixel(GLuint x, GLuint y, glm::vec3 color) {
	const int bpp = 3;
	
	GLubyte r = color.x * 255;
	GLubyte g = color.y * 255;
	GLubyte b = color.z * 255;
	
	const int i = (x * bpp) + y * (_width * bpp);
	_resultData[i + 0] = r;
	_resultData[i + 1] = g;
	_resultData[i + 2] = b;
}

void RayTracer::render(const Scene& scene, const Camera& cam) {
	//*
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			
			Ray ray = cam.rayFromPixel(j, i);
			
			bool hit = false;
			float nearestDist = 100000000.0f;
			Primitive* nearestPrim = nullptr;
			auto primitives = scene.primitives();
			
			// Find nearest primitive
			for (auto& p : primitives) {
				float dist;
				HitTestResult res = p->intersect(ray, dist);
				if (res == HitTestResult::HIT) {
					hit = true;
					if (dist < nearestDist) {
						nearestDist = dist;
						nearestPrim = p;
					}
				}
			}
			
			
			// Get color of the primitive
			if (hit) {
				//glm::vec3 intersect = ray.origin() + ray.direction() * nearestDist;
				setPixel(j, i, nearestPrim->material().diffuse());
			}
			
			
		}
	}
	//*/
	
}