// Rasterisation: geometry in, pixels out.
#ifndef RENDERER_H
#define RENDERER_H

#include "Framebuffer.h"

// A corner after projection: pixel position plus depth. Not a Vec3 -- these are
// three unrelated quantities, and the separate type stops a model-space point
// reaching the rasteriser.
struct ScreenVertex {
	float x = 0.0f;
	float y = 0.0f;
	float depth = 0.0f;   // larger is nearer
};

struct ScreenTriangle {
	ScreenVertex a;
	ScreenVertex b;
	ScreenVertex c;
};

class Renderer {
public:
	explicit Renderer(Framebuffer& target) : m_target(target) {}

	// Fills an already-projected triangle. Needs no mesh and no camera.
	void draw_triangle(const ScreenTriangle& tri, Color color);

	// Discard faces turned away from the camera. Not needed for correctness
	// once depth testing is on; roughly a 2x speedup.
	void set_backface_culling(bool enabled) { m_cull_backfaces = enabled; }
	bool backface_culling() const { return m_cull_backfaces; }

private:
	Framebuffer& m_target;
	bool m_cull_backfaces = true;
};

#endif
