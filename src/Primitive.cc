#include "Primitive.h"

////////////////////////////////////////
// Sphere definitions
////////////////////////////////////////
HitTestResult Sphere::intersect(const Ray& ray, float& dist) const {
	
	//*
	glm::vec3 rayToSphere = _centre - ray.origin();
	
	
	if (glm::dot(rayToSphere, ray.direction()) >= 0) {
		
		glm::vec3 projCentre = ray.origin() + glm::dot(rayToSphere, ray.direction()) * ray.direction();
		
		float projDist = glm::distance(projCentre, _centre);
		if (projDist <= _radius) {
			float d = sqrt(_radius * _radius - projDist * projDist);
			
			
			if (glm::length(rayToSphere) >= _radius) {
				float hitDist = glm::length(projCentre - ray.origin()) - d;
				if (hitDist < dist) {
					dist = hitDist;
					return HitTestResult::HIT;
				}
			} else {
				float hitDist = glm::length(projCentre - ray.origin()) + d;
				if (hitDist < dist) {
					//dist = hitDist;
					return HitTestResult::INSIDE;
				}
				
			}
		}
	}
	//*/
	return HitTestResult::MISS;
}
glm::vec3 Sphere::getNormal(const glm::vec3& p) const {
	return (p - _centre) * _radius;
}



////////////////////////////////////////
// Triangle definitions
////////////////////////////////////////
Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) : _v1(v1), _v2(v2), _v3(v3) {
	_normal = glm::normalize(glm::cross(_v2 - _v1, _v3 - _v1));
}
HitTestResult Triangle::intersect(const Ray& ray, float& dist) const {
	const float EPSILON = 0.000001f;
	glm::vec3 e1, e2;
	glm::vec3 P, Q, T;
	float det, invDet, u, v;
	float t;
	
	e1 = _v2 - _v1;
	e2 = _v3 - _v1;
	
	
	P = glm::cross(ray.direction(), e2);
	det = glm::dot(e1, P);
	
	if (det > -EPSILON && det < EPSILON) return HitTestResult::MISS;
	invDet = 1.0f / det;
	
	T = ray.origin() - _v1;
	u = glm::dot(T, P) * invDet;
	if (u < 0.0f || u > 1.0f) return HitTestResult::MISS;
	
	
	Q = glm::cross(T, e1);
	v = glm::dot(ray.direction(), Q) * invDet;
	if (v < 0.0f || u + v > 1.0f) return HitTestResult::MISS;
	
	
	t = glm::dot(e2, Q) * invDet;
	if (abs(t) > EPSILON) {
		dist = t;
		return HitTestResult::HIT;
	}
	
	return HitTestResult::MISS;
}




////////////////////////////////////////
// Plane definitions
////////////////////////////////////////
HitTestResult Plane::intersect(const Ray& ray, float& dist) const {
	float d = glm::dot(ray.direction(), _normal);
	if (d != 0) {
		float hitDist = -(glm::dot(_normal, ray.origin()) + _d) / d;
		if (hitDist >= 0) {
			if (hitDist < dist) {
				dist = hitDist;
				return HitTestResult::HIT;
			}
		}
	}
	return HitTestResult::MISS;
}