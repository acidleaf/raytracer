#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include "RayTracer.h"

class Camera {
protected:
	glm::vec3 _eye, _centre, _up;
	glm::vec3 _u, _v, _n;
	
	GLfloat _imgW, _imgH;
	GLfloat _fov;
	GLfloat _aspectRatio = 1.0f;
	
	void calcUVN();
	
public:
	
	bool init(GLuint imgW, GLuint imgH, GLfloat fov, glm::vec3 eye, glm::vec3 centre, glm::vec3 up);
	
	Ray rayFromPixel(GLuint x, GLuint y, GLfloat dx = 0.0f, GLfloat dy = 0.0f) const;
	
	GLfloat focalLength() const;
	
	
	glm::vec3 eye() const { return _eye; }
	void eye(glm::vec3& eye);
	
	glm::vec3 centre() const { return _centre; }
	void centre(glm::vec3& centre);
	
	glm::vec3 up() const { return _up; }
	void up(glm::vec3& up);
	
	GLfloat FOV() const { return _fov; }
	void FOV(GLfloat fov) { _fov = fov; }
	
};


#endif