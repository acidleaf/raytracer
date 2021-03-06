#include "Camera.h"
#include <cmath>

bool Camera::init(GLuint imgW, GLuint imgH, GLfloat fov, glm::vec3 eye, glm::vec3 centre, glm::vec3 up) {
	_imgW = imgW;
	_imgH = imgH;
	_fov = fov;
	
	_aspectRatio = (float)_imgW / (float)imgH;
	
	_eye = eye;
	_centre = centre;
	_up = up;
	
	calcUVN();
	
	return true;
}

GLfloat Camera::focalLength() const {
	// 0.5 as the viewing plane is in normalized coordinates (y = -0.5 to 0.5)
	return 0.5f / tan(glm::radians(_fov * 0.5f));
}

Ray Camera::rayFromPixel(GLuint x, GLuint y, GLfloat dx, GLfloat dy) const {
	float nx = ((x / (float)_imgW) - 0.5f) * _aspectRatio;
	float ny = (y / (float)_imgH) - 0.5f;
	
	float f = focalLength();
	glm::vec3 imgPoint = nx * _u + ny * _v + _eye + _n * f;
	
	return Ray{
		imgPoint,
		(imgPoint - _eye) + glm::vec3{dx, dy, 0.0f}
	};
}

void Camera::calcUVN() {
	_n = glm::normalize(_centre - _eye);
	_u = glm::normalize(glm::cross(_n, _up));
	_v = glm::normalize(glm::cross(_n, _u));
	
}

void Camera::eye(glm::vec3& eye) {
	_eye = eye;
	calcUVN();
}

void Camera::centre(glm::vec3& centre) {
	_centre = centre;
	calcUVN();
}

void Camera::up(glm::vec3& up) {
	_up = up;
	calcUVN();
}
