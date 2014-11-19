#include "Primitive.h"

HitTestResult Sphere::intersect(Ray& ray, float& dist) const {
	
	HitTestResult res = HitTestResult::MISS;
	glm::vec3 rayToSphere = _centre - ray.origin();
	
	
	if (glm::dot(rayToSphere, ray.direction()) >= 0) {
		
		glm::vec3 projCentre = ray.origin() + glm::dot(rayToSphere, ray.direction()) * ray.direction();
		
		float projDist = glm::distance(projCentre, _centre);
		if (projDist <= _radius) {
			float d = sqrt(_radius * _radius - projDist * projDist);
			
			
			if (glm::length(rayToSphere) >= _radius) {
				dist = glm::length(projCentre - ray.origin()) - d;
				res = HitTestResult::HIT;
			} else {
				dist = glm::length(projCentre - ray.origin()) + d;
				res = HitTestResult::INSIDE;
			}
			
			// The intersection point
			//glm::vec3 intersect = ray.origin() + ray.direction() * dist;
		}
	}
	
	return res;
}
glm::vec3 Sphere::getNormal(const glm::vec3& p) const {
	return (p - _centre) * _radius;
}