#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector2_ {
	float x;
	float y;
} vec2_t;

typedef struct vector3_ {
	float x;
	float y;
	float z;
} vec3_t;
// TODO: Add functions to manupilate 2d and 3d
vec3_t vec3RotateX(vec3_t v, float angle);
vec3_t vec3RotateY(vec3_t v, float angle);
vec3_t vec3RotateZ(vec3_t v, float angle);
#endif
