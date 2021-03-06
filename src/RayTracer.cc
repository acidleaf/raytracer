#include "RayTracer.h"
#include "Camera.h"
#include "Scene.h"

Ray::Ray() : _origin(glm::vec3(0)), _direction(glm::vec3(0)) {}

Ray::Ray(glm::vec3 origin, glm::vec3 direction) : _origin(origin), _direction(glm::normalize(direction)) {}



// Raytracer definitions

const float RayTracer::EPSILON = 0.0001f;

bool RayTracer::init(GLuint width, GLuint height) {
	if (width == 0 || height == 0) return false;
	_width = width;
	_height = height;
	
	_dx = (1.0f / _width) * ((float)_width / (float)_height);
	_dy = 1.0f / _height;
	
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

Primitive* RayTracer::traceRay(const Scene& scene, const Ray& ray, glm::vec3& accColor, float& depth, float rIndex, int bounce) {
	if (bounce > TRACE_DEPTH) return nullptr;
	
	depth = 100000.0f;
	Primitive* prim = nullptr;
	auto primitives = scene.primitives();
	
	HitTestResult result = HitTestResult::MISS;
	
	// Find nearest primitive
	for (auto& p : primitives) {
		
		if (p->isLight()) continue;
		
		HitTestResult res = p->intersect(ray, depth);
		if (res == HitTestResult::HIT) {
			prim = p;
			result = res;
		}
	}
	
	
	if (!prim) return prim;
	
	
	// Set the light color if it's a light
	if (prim->isLight()) {
		accColor = prim->material().diffuseColor() * prim->material().diffuseIntensity();
		return prim;
	}
	
	// Trace the lights
	glm::vec3 intersect = ray.origin() + ray.direction() * depth;
	for (auto& l : primitives) {
		if (l == prim) continue;
		if (l->isLight()) {
			
			// Ray from intersection point to light
			glm::vec3 L = ((Sphere*)l)->centre() - intersect;
			
			// Point light falloff
			float lDist = glm::length(L);
			L *= (1.0f / lDist);
			
			// Shadows
			// Check for each object in the scene if it blocks a ray from the current light to this intersection point
			float shade = 1.0f;
			for (auto& p : primitives) {
				if (p != l && p != prim && !p->isLight() && p->intersect(Ray{intersect + L * EPSILON, L}, lDist)) {
					shade = 0.0f;
					break;
				}
			}
			
			// Normal at point of intersection
			glm::vec3 N = glm::normalize(prim->getNormal(intersect));
			
			// Diffuse shading
			if (prim->material().diffuseIntensity() > 0) {
				float dotProd = glm::dot(N, L);
				if (dotProd > 0) {
					glm::vec3 primColor = prim->material().diffuseColor() * prim->material().diffuseIntensity();
					glm::vec3 lightColor = l->material().diffuseColor() * l->material().diffuseIntensity();
					accColor += dotProd * primColor * lightColor * shade;
				}
			}
			
			// Specular shading (Phong)
			if (prim->material().specularIntensity() > 0) {
				glm::vec3 V = ray.direction();
				glm::vec3 R = L - 2.0f * glm::dot(L, N) * N;
				float dotProd = glm::dot(V, R);
				if (dotProd > 0) {
					float spec = std::pow(dotProd, prim->material().specularExp()) * prim->material().specularIntensity() * shade;
					accColor += spec * prim->material().specularColor();
				}
			}
		}
	}
	
	// Reflection
	// Calculate the reflected ray direction and trace it from the current intersection point
	float refl = prim->material().reflection();
	if (refl > 0) {
		glm::vec3 N = prim->getNormal(intersect);
		glm::vec3 R = ray.direction() - 2.0f * glm::dot(ray.direction(), N) * N;
		
		if (bounce < TRACE_DEPTH) {
			glm::vec3 reflCol{0};
			float dist;
			traceRay(scene, Ray{intersect + R * EPSILON, R}, reflCol, dist, rIndex, bounce + 1);
			accColor += refl * reflCol * prim->material().diffuseColor();
		}
	}
	
	
	// Refraction
	float refr = prim->material().refraction();
	if (refr > 0 && bounce < TRACE_DEPTH) {
		float ri = prim->material().refractiveIndex();
		float n = rIndex / ri;
		
		glm::vec3 N = prim->getNormal(intersect) * (float)result;
		
		float cosI = -glm::dot(N, ray.direction());
		float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);
		
		if (cosT2 > 0.0f) {
			glm::vec3 T = (n * ray.direction()) + (n * cosI - std::sqrt(cosT2)) * N;
			glm::vec3 refrCol{0};
			float dist;
			traceRay(scene, Ray{intersect + T * EPSILON, T}, refrCol, dist, ri, bounce + 1);
			
			glm::vec3 absorbance = prim->material().diffuseColor() * 0.15f * dist;
			glm::vec3 transparency{
				std::exp(absorbance.x),
				std::exp(absorbance.y),
				std::exp(absorbance.z)
			};
			
			
			accColor += refrCol;
		}
	}
	return prim;
}

void RayTracer::render(const Scene& scene, const Camera& cam) {
	Primitive* lastPrim = nullptr;
	const bool supersampling = false;
	
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			
			glm::vec3 accColor{0};
			Ray ray = cam.rayFromPixel(j, i);
			float depth;
			Primitive* p = traceRay(scene, ray, accColor, depth, 1.0f, 0);
			
			if (p != lastPrim && supersampling) {
				lastPrim = p;
				for (int ty = -1; ty < 2; ++ty) {
					for (int tx = -1; tx < 2; ++tx) {
						Ray ray = cam.rayFromPixel(j, i, tx * _dx, ty * _dy);
						traceRay(scene, ray, accColor, depth, 1.0f, 0);
					}
				}
				setPixel(j, i, accColor / 9.0f);
			} else {
				setPixel(j, i, accColor);
			}
			
			
			
		}
	}
}