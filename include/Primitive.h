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
	glm::vec3 _diffuse;
	
public:
	void diffuse(glm::vec3 diffuse) { _diffuse = diffuse; }
	glm::vec3 diffuse() { return _diffuse; }
	
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
	
	virtual HitTestResult intersect(Ray& ray, float& dist) const = 0;
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
	HitTestResult intersect(Ray& ray, float& dist) const;
	glm::vec3 getNormal(const glm::vec3& p) const;
};

#endif