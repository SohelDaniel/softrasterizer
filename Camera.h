// View and projection transforms. Rebuilt when the camera moves, not per vertex.
#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Vec3.h"

class Camera {
public:
	// `up` is a hint; it is re-orthogonalised against the view direction.
	Camera(Vec3 eye, Vec3 center, Vec3 up);

	void set_eye(Vec3 eye);
	void set_center(Vec3 center);
	void set_up(Vec3 up);

	Vec3 eye() const    { return m_eye; }
	Vec3 center() const { return m_center; }
	Vec3 up() const     { return m_up; }

	const Mat4& view() const       { return m_view; }
	const Mat4& projection() const { return m_projection; }

	// World position -> normalised device coordinates, about -1..1 per axis.
	Vec3 project(Vec3 world) const;

private:
	void rebuild();

	Vec3 m_eye;
	Vec3 m_center;
	Vec3 m_up;
	Mat4 m_view;
	Mat4 m_projection;
};

#endif
