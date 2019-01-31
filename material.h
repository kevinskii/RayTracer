#pragma once
#include "hitable.h"
#include "drand48.h"

// Finds a random point in a sphere with unit radius centered at the origin
vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0f);
	return p;
}

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};