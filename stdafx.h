#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef unsigned int uint;

struct Vector2D {
  	float x;
	float y;
};
struct Vector3D {
	float x;
	float y;
	float z;
};

struct Face {
	uint16 x;
	uint16 y;
	uint16 z;
};
