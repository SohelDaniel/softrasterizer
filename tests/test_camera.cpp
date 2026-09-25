#include "test.h"

#include "Camera.h"

void test_camera() {
	const Camera cam({0, 0, 5}, {0, 0, 0}, {0, 1, 0});

	// The target sits at the centre of the view.
	const Vec3 origin = cam.project({0, 0, 0});
	CHECK_NEAR(origin.x, 0.0);
	CHECK_NEAR(origin.y, 0.0);

	// Axes are not mirrored.
	CHECK(cam.project({1, 0, 0}).x > 0.0f);
	CHECK(cam.project({0, 1, 0}).y > 0.0f);

	// Perspective: the same offset covers less screen when further away.
	const float near_x = cam.project({1, 0, 1}).x;
	const float far_x  = cam.project({1, 0, -1}).x;
	CHECK(near_x > far_x);

	// Nearer geometry gets the larger depth, which is what the z-test expects.
	CHECK(cam.project({0, 0, 1}).z > cam.project({0, 0, -1}).z);

	// Moving the eye rebuilds the transform. Sampled off the target plane,
	// which is unscaled by construction and so would not change.
	Camera moving({0, 0, 5}, {0, 0, 0}, {0, 1, 0});
	const float before = moving.project({1, 0, 1}).x;
	moving.set_eye({0, 0, 10});
	CHECK(moving.project({1, 0, 1}).x != before);

	// Pulling back flattens the perspective.
	CHECK(moving.project({1, 0, 1}).x < before);

	// A non-perpendicular up hint is re-orthogonalised, not rejected.
	const Camera tilted({0, 0, 5}, {0, 0, 0}, {0.3f, 1, 0.7f});
	CHECK_NEAR(tilted.project({0, 0, 0}).x, 0.0);
}
