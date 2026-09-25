// 3D vector: vertex positions from the .obj, and directions derived from them.
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <stdexcept>

struct Vec3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3() = default;
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	float& operator[](int i) {
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		throw std::out_of_range("Vec3 index out of range");
	}
	const float& operator[](int i) const {
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		throw std::out_of_range("Vec3 index out of range");
	}
};

inline Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
inline Vec3 operator-(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
inline Vec3 operator-(Vec3 v)         { return {-v.x, -v.y, -v.z}; }
inline Vec3 operator*(Vec3 v, float s) { return {v.x * s, v.y * s, v.z * s}; }
inline Vec3 operator*(float s, Vec3 v) { return v * s; }
inline Vec3 operator/(Vec3 v, float s) { return {v.x / s, v.y / s, v.z / s}; }

inline Vec3& operator+=(Vec3& a, Vec3 b) { a = a + b; return a; }
inline Vec3& operator-=(Vec3& a, Vec3 b) { a = a - b; return a; }
inline Vec3& operator*=(Vec3& v, float s) { v = v * s; return v; }
inline Vec3& operator/=(Vec3& v, float s) { v = v / s; return v; }

inline float dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// Perpendicular to both; its sign encodes their winding.
inline Vec3 cross(Vec3 a, Vec3 b) {
	return {a.y * b.z - a.z * b.y,
	        a.z * b.x - a.x * b.z,
	        a.x * b.y - a.y * b.x};
}

inline float norm2(Vec3 v) { return dot(v, v); }
inline float norm(Vec3 v)  { return std::sqrt(norm2(v)); }

// Zero vector maps to zero rather than NaN.
inline Vec3 normalized(Vec3 v) {
	const float n = norm(v);
	return n > 0.0f ? v / n : Vec3{};
}

#endif
