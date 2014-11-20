#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <glm/glm.hpp>
#include "RayTracer.h"


// Hit test result
enum HitTestResult {
	HIT = 1,
	MISS = 0,
	INSIDE = -1
};



////////////////////////////////////////
// Material class definition
////////////////////////////////////////
class Material {
protected:
	glm::vec3 _diffuseColor;
	float _diffuseIntensity;
	
public:
	void diffuse(float intensity, glm::vec3 color) { _diffuseIntensity = intensity; _diffuseColor = color; }
	float diffuseIntensity() const { return _diffuseIntensity; }
	glm::vec3 diffuseColor() const { return _diffuseColor; }
	
};


////////////////////////////////////////
// Primitive class definition
////////////////////////////////////////
class Primitive {
protected:
	Material _material;
	bool _isLight = false;
	
public:
	virtual ~Primitive() {}
	
	virtual HitTestResult intersect(const Ray& ray, float& dist) const = 0;
	virtual glm::vec3 getNormal(const glm::vec3& p) const = 0; 
	
	Material& material() { return _material; }
	void setMaterial(Material& m) { _material = m; }
	
	
	void light(bool isLight) { _isLight = isLight; }
	bool isLight() const { return _isLight; }
};


////////////////////////////////////////
// Sphere primitive
////////////////////////////////////////
class Sphere : public Primitive {
protected:
	glm::vec3 _centre;
	float _radius;
	
public:
	~Sphere() {}
	
	Sphere(glm::vec3 centre, float radius) : _centre(centre), _radius(radius) {}
	HitTestResult intersect(const Ray& ray, float& dist) const;
	glm::vec3 getNormal(const glm::vec3& p) const;
	
	glm::vec3 centre() const { return _centre; }
	float radius() const { return _radius; }
};



////////////////////////////////////////
// Plane primitive
////////////////////////////////////////
class Plane : public Primitive {
protected:
	glm::vec3 _normal;
	float _d;
	
public:
	Plane(glm::vec3 normal, float d) : _normal(glm::normalize(normal)), _d(d) {}
	HitTestResult intersect(const Ray& ray, float& dist) const;
	glm::vec3 getNormal(const glm::vec3& p) const { return _normal; }
	
	float d() const { return _d; }
};

#endif