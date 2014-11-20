#include "Primitive.h"

////////////////////////////////////////
// Sphere definitions
////////////////////////////////////////
HitTestResult Sphere::intersect(const Ray& ray, float& dist) const {
	
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
				//float hitDist = glm::length(projCentre - ray.origin()) + d;
				return HitTestResult::INSIDE;
			}
		}
	}
	
	return HitTestResult::MISS;
}
glm::vec3 Sphere::getNormal(const glm::vec3& p) const {
	return (p - _centre) * _radius;
}


////////////////////////////////////////
// Plane definitions
////////////////////////////////////////
HitTestResult Plane::intersect(const Ray& ray, float& dist) const {
	float d = glm::dot(ray.direction(), _normal);
	if (d != 0) {
		float hitDist = -glm::dot(_normal, ray.origin()) + _d / d;
		if (hitDist >= 0) {
			if (hitDist < dist) {
				dist = hitDist;
				return HitTestResult::HIT;
			}
		}
	}
	return HitTestResult::MISS;
}