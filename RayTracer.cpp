// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <random>
#include "pch.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "float.h"


double drand48() {
	// Ref: http://forums.codeguru.com/showthread.php?525211-How-to-use-drand48()-for-Windows
	return rand() / (RAND_MAX + 1.0);
}

vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		return 0.5f * vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
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
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);
			int ir = int(255.99f*col[0]);
			int ig = int(255.99f*col[1]);
			int ib = int(255.99f*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}