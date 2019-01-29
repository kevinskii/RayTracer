#pragma once
#include "material.h"
#include "ray.h"
#include "drand48.h"

// Finds a random point in a sphere with unit radius centered at the origin
vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0f);
	return p;
}

// For diffuse materials
class lambertian : public material {
public:
	lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};