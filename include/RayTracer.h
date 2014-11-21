#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__


#include <glm/glm.hpp>



class Ray {
protected:
	glm::vec3 _origin, _direction;
public:
	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction);
	glm::vec3 origin() const { return _origin; }
	glm::vec3 direction() const { return _direction; }
};





class Scene;
class Camera;
class Primitive;

class RayTracer {
protected:
	static const int TRACE_DEPTH = 6;
	static const float EPSILON;
	
	GLuint _width, _height;
	GLubyte* _resultData;
	
	void setPixel(GLuint x, GLuint y, glm::vec3 color);
	
	Primitive* traceRay(const Scene& scene, const Ray& ray, glm::vec3& acc, float& depth, float rIndex, int bounce);
	
public:
	bool init(GLuint width, GLuint height);
	void release();
	
	void render(const Scene& scene, const Camera& cam);
	
	const GLubyte* resultData() { return _resultData; }
};

#endif