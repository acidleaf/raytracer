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
	
	GLubyte r = std::min(255, (int)(color.x * 256));
	GLubyte g = std::min(255, (int)(color.y * 256));
	GLubyte b = std::min(255, (int)(color.z * 256));
	
	const int i = (x * bpp) + y * (_width * bpp);
	_resultData[i + 0] = r;
	_resultData[i + 1] = g;
	_resultData[i + 2] = b;
}

void RayTracer::traceRay(const Scene& scene, const Ray& ray, glm::vec3& accColor) {
	bool hit = false;
	float dist = 100000000.0f;
	Primitive* prim = nullptr;
	auto primitives = scene.primitives();
	
	// Find nearest primitive
	for (auto& p : primitives) {
		HitTestResult res = p->intersect(ray, dist);
		if (res == HitTestResult::HIT) {
			hit = true;
			prim = p;
		}
	}
	
	//if (hit) accColor = nearestPrim->material().diffuse();
	
	///*
	if (hit) {
		// Set the light color if it's a light
		if (prim->isLight()) {
			accColor = prim->material().diffuseColor() * prim->material().diffuseIntensity();
			return;
		}
		
		// Trace the lights
		glm::vec3 intersect = ray.origin() + ray.direction() * dist;
		for (auto& l : primitives) {
			if (l == prim) continue;
			if (l->isLight()) {
				glm::vec3 L = glm::normalize(((Sphere*)l)->centre() - intersect);
				glm::vec3 N = prim->getNormal(intersect);
				
				float dotProd = glm::dot(N, L);
				if (dotProd > 0) {
					glm::vec3 primColor = prim->material().diffuseColor() * prim->material().diffuseIntensity();
					glm::vec3 lightColor = l->material().diffuseColor() * l->material().diffuseIntensity();
					accColor += dotProd * primColor * lightColor;
				}
			}
		}
	}
	//*/
}

void RayTracer::render(const Scene& scene, const Camera& cam) {
	//*
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			
			Ray ray = cam.rayFromPixel(j, i);
			glm::vec3 accColor{0};
			
			traceRay(scene, ray, accColor);
			
			setPixel(j, i, accColor);
		}
	}
	//*/
	
}