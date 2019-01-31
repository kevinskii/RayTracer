#pragma once
#include <random>

// Mimics the drand48() library function in the book that generates a random number in [0,1.0).
float drand48() {
	// Ref: http://forums.codeguru.com/showthread.php?525211-How-to-use-drand48()-for-Windows
	return (float)(rand() / (RAND_MAX + 1.0));
}
