#include "Matrix.h"

Mat4 Mat4::identity() {
	Mat4 out;
	for (int i = 0; i < 4; i++) out[i][i] = 1.0f;
	return out;
}

Mat4 Mat4::translation(Vec3 t) {
	Mat4 out = identity();
	out[0][3] = t.x;
	out[1][3] = t.y;
	out[2][3] = t.z;
	return out;
}

Mat4 operator*(const Mat4& a, const Mat4& b) {
	Mat4 out;
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			for (int k = 0; k < 4; k++)
				out[r][c] += a[r][k] * b[k][c];
	return out;
}

Vec3 transform_point(const Mat4& mat, Vec3 v) {
	const float in[4] = {v.x, v.y, v.z, 1.0f};
	float out[4] = {};
	for (int r = 0; r < 4; r++)
		for (int k = 0; k < 4; k++)
			out[r] += mat[r][k] * in[k];

	if (out[3] != 0.0f) {
		out[0] /= out[3];
		out[1] /= out[3];
		out[2] /= out[3];
	}
	return {out[0], out[1], out[2]};
}

Vec3 transform_direction(const Mat4& mat, Vec3 v) {
	const float in[3] = {v.x, v.y, v.z};
	float out[3] = {};
	for (int r = 0; r < 3; r++)
		for (int k = 0; k < 3; k++)
			out[r] += mat[r][k] * in[k];
	return {out[0], out[1], out[2]};
}
