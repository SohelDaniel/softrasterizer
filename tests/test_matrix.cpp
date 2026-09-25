#include "test.h"

#include "Matrix.h"

void test_matrix() {
	const Mat4 id = Mat4::identity();
	const Vec3 p = {1.0f, 2.0f, 3.0f};

	CHECK_NEAR(transform_point(id, p).x, 1.0);
	CHECK_NEAR(transform_point(id, p).z, 3.0);

	const Mat4 t = Mat4::translation({10.0f, 0.0f, -5.0f});
	CHECK_NEAR(transform_point(t, p).x, 11.0);
	CHECK_NEAR(transform_point(t, p).z, -2.0);

	// A direction ignores translation.
	CHECK_NEAR(transform_direction(t, p).x, 1.0);

	// Identity is the multiplicative unit.
	const Mat4 ti = t * id;
	CHECK_NEAR(transform_point(ti, p).x, 11.0);

	// Composition applies the right-hand matrix first.
	const Mat4 t2 = Mat4::translation({1.0f, 1.0f, 1.0f});
	CHECK_NEAR(transform_point(t * t2, p).x, 12.0);

	// A non-unit w divides through: that is the perspective divide.
	Mat4 half = Mat4::identity();
	half[3][3] = 2.0f;
	CHECK_NEAR(transform_point(half, p).y, 1.0);
}
