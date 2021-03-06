#pragma once
#include "MathLibrary.hpp"
#include "Ray.hpp"
#include "objectToTrace.hpp"

class Sphere : public objectToTrace
{
public:

	vec3 centerSphere;
	float radius;

	bool hit(const Ray& ray, hit_record& record) const;

	Sphere(vec3 center, float m_radius, vec3 color);
	~Sphere();

	// Inherited via objectToTrace
	virtual vec3 getColor(hit_record record, Scene * scene) const;
};


