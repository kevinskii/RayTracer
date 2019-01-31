#pragma once
#include "material.h"
#include "ray.h"

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n)*n;
}

class metal : public material {
public:
	metal(const vec3& a, float f) : albedo(a) { 
		// Spheres, for example, may have fuzzy reflections depending on the size of the sphere,
		// where larger spheres create fuzzier reflections. Set a max fuzz of 1.
		if (f < 1) {
			fuzz = f;
		}
		else {
			fuzz = 1;
		}
	}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};
