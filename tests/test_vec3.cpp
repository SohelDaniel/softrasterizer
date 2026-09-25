#include "test.h"

#include "Vec3.h"

void test_vec3() {
	const Vec3 a = {1.0f, 2.0f, 3.0f};
	const Vec3 b = {4.0f, 5.0f, 6.0f};

	CHECK((a + b).x == 5.0f);
	CHECK((b - a).y == 3.0f);
	CHECK((a * 2.0f).z == 6.0f);
	CHECK((2.0f * a).z == 6.0f);
	CHECK((b / 2.0f).x == 2.0f);
	CHECK((-a).x == -1.0f);

	Vec3 c = a;
	c += b;
	CHECK(c.z == 9.0f);

	CHECK_NEAR(dot(a, b), 32.0);

	// Right-handed: x cross y is z.
	const Vec3 n = cross({1, 0, 0}, {0, 1, 0});
	CHECK_NEAR(n.x, 0.0);
	CHECK_NEAR(n.y, 0.0);
	CHECK_NEAR(n.z, 1.0);

	// Anti-commutative.
	CHECK_NEAR(cross(a, b).x, -cross(b, a).x);

	CHECK_NEAR(norm2({3, 4, 0}), 25.0);
	CHECK_NEAR(norm({3, 4, 0}), 5.0);
	CHECK_NEAR(norm(normalized({3, 4, 0})), 1.0);

	// Degenerate input must not produce NaN.
	CHECK(norm(normalized({0, 0, 0})) == 0.0f);

	CHECK(a[0] == 1.0f && a[2] == 3.0f);
	bool threw = false;
	try { (void)a[3]; } catch (const std::out_of_range&) { threw = true; }
	CHECK(threw);
}
