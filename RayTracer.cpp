// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ray.h"


bool hit_sphere(const vec3& center, float radius, const ray& r) {
	/*
	A point is on a sphere that is centered at (cx,cy,cz) if:
	(x-cx)(x-cx) + (y-cy)(y-cy) + (z-cz)(z-cz) = R*R
	= dot((p-C),(p-C)) where (p-C) is the vector from the center C=(cx,cy,cz) to point
	p=(x,y,z).

	If a point is on the sphere, this will be true: dot((p(t)-c),(p(t)-c)) = R*R, or 
	equivalently: dot((A+t*B - C),(A + t*B-C)) = R*R.

	Expanding the terms and moving terms to left side gives us:
	t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0;
	*/
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	return (discriminant > 0);
}


vec3 color(const ray& r) {
	// If on some arbitrary sphere, color red
	if (hit_sphere(vec3(0, 0, -1), 0.5f, r)) {
		return vec3(1, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}


int main()
{
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99f*col[0]);
			int ig = int(255.99f*col[1]);
			int ib = int(255.99f*col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}