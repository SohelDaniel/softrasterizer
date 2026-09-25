// 4x4 transforms. Row-major: m[row][col].
// Four dimensions rather than three so a single matrix can also translate and
// carry the perspective divide.
#ifndef MATRIX_H
#define MATRIX_H

#include "Vec3.h"

struct Mat4 {
	float m[4][4] = {};

	float*       operator[](int row)       { return m[row]; }
	const float* operator[](int row) const { return m[row]; }

	static Mat4 identity();
	static Mat4 translation(Vec3 t);
};

// Composition: (a * b) applies b first.
Mat4 operator*(const Mat4& a, const Mat4& b);

// Treats v as a point (w = 1) and divides through by the resulting w.
Vec3 transform_point(const Mat4& mat, Vec3 v);

// Treats v as a direction (w = 0), so translation does not apply.
Vec3 transform_direction(const Mat4& mat, Vec3 v);

#endif
