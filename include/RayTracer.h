#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__


#include <glm/glm.hpp>



class Ray {
protected:
	glm::vec3 _origin, _direction;
public:
	Ray();
	Ray(glm::vec3& origin, glm::vec3& direction);
	glm::vec3 origin() { return _origin; }
	glm::vec3 direction() { return _direction; }
};





class Scene;
class Camera;

class RayTracer {
protected:
	GLuint _width, _height;
	GLubyte* _resultData;
	
	void setPixel(GLuint x, GLuint y, glm::vec3 color);
	
public:
	bool init(GLuint width, GLuint height);
	void release();
	
	void render(const Scene& scene, const Camera& cam);
	
	const GLubyte* resultData() { return _resultData; }
};

#endif