#include "Primitive.h"

HitTestResult Sphere::intersect(Ray& ray, float& dist) const {
	return HitTestResult::HIT;
}
glm::vec3 Sphere::getNormal() const {
	return glm::vec3(0, 1, 0);
}