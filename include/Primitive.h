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
	float _diffuseIntensity = 1.0f;
	
	glm::vec3 _specularColor;
	float _specularIntensity;
	float _specularExp;
	
	float _reflection = 0.0f;
	
	float _refraction = 0.0f;
	float _refractiveIndex = 1.0f;
	
public:
	void diffuse(float intensity, glm::vec3 color) { _diffuseIntensity = intensity; _diffuseColor = color; }
	float diffuseIntensity() const { return _diffuseIntensity; }
	glm::vec3 diffuseColor() const { return _diffuseColor; }
	
	void specular(float intensity, float exp, glm::vec3 color) { _specularIntensity = intensity; _specularExp = exp; _specularColor = color; }
	float specularExp() const { return _specularExp; }
	float specularIntensity() const { return _specularIntensity; }
	glm::vec3 specularColor() const { return _specularColor; }
	
	void reflection(float intensity) { _reflection = intensity; }
	float reflection() const { return _reflection; }
	
	void refraction(float intensity, float index) { _refraction = intensity; _refractiveIndex = index; }
	float refraction() const { return _refraction; }
	float refractiveIndex() const { return _refractiveIndex; }
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
	Plane(glm::vec3 normal, glm::vec3 p) : _normal(glm::normalize(normal)), _d(-glm::dot(_normal, p)) {}
	HitTestResult intersect(const Ray& ray, float& dist) const;
	glm::vec3 getNormal(const glm::vec3& p) const { return _normal; }
	
	float d() const { return _d; }
};

#endif