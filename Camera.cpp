#include "Camera.h"

Camera::Camera(Vec3 eye, Vec3 center, Vec3 up)
	: m_eye(eye), m_center(center), m_up(up) {
	rebuild();
}

void Camera::set_eye(Vec3 eye)       { m_eye = eye;       rebuild(); }
void Camera::set_center(Vec3 center) { m_center = center; rebuild(); }
void Camera::set_up(Vec3 up)         { m_up = up;         rebuild(); }

void Camera::rebuild() {
	// Orthonormal basis; forward points from the target back to the eye.
	const Vec3 forward = normalized(m_eye - m_center);
	const Vec3 right   = normalized(cross(m_up, forward));
	const Vec3 true_up = cross(forward, right);

	Mat4 rotation = Mat4::identity();
	rotation[0][0] = right.x;   rotation[0][1] = right.y;   rotation[0][2] = right.z;
	rotation[1][0] = true_up.x; rotation[1][1] = true_up.y; rotation[1][2] = true_up.z;
	rotation[2][0] = forward.x; rotation[2][1] = forward.y; rotation[2][2] = forward.z;

	m_view = rotation * Mat4::translation(-m_center);

	// Divide by (1 - z/f) so distant geometry shrinks. f is the eye-to-target
	// distance, leaving the target plane unscaled.
	const float f = norm(m_eye - m_center);
	m_projection = Mat4::identity();
	if (f > 0.0f) m_projection[3][2] = -1.0f / f;
}

Vec3 Camera::project(Vec3 world) const {
	return transform_point(m_projection * m_view, world);
}
