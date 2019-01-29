// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "pch.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "float.h"
#include "material.h"
#include "drand48.h"


vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	// use 0.001f rather than 0.0f for t_min to get rid of the "shadow acne" problem (Ch 7).
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5f * color(ray(rec.p, target - rec.p), world);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	// From bottom to top
	for (int j = ny - 1; j >= 0; j--) {
		// From left to right
		for (int i = 0; i < nx; i++) {

			// Choose the color of this ray based on random samples of several close by locations
			// to as to anti-alias, i.e. to blur the edges of objects so they look smoother and less
			// jagged.
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);

			// Most image viewers assume the image is gamma corrected, so they make it darker.
			// Use "gamma 2", i.e. raise the color to the power 1/gamma=1/2, i.e. take the square root.
			col = vec3(sqrt(col[0]), (col[1]), (col[2]));

			int ir = int(255.99f*col[0]);
			int ig = int(255.99f*col[1]);
			int ib = int(255.99f*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}