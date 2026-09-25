#include "test.h"

#include "Camera.h"
#include "Framebuffer.h"
#include "Mesh.h"
#include "Renderer.h"

#include <cstdio>
#include <fstream>

void test_renderer() {
	// Right triangle with legs of 100px: area 5000, plus the boundary.
	const ScreenTriangle tri = {{10, 10, 0}, {110, 10, 0}, {10, 110, 0}};

	Framebuffer fb(200, 200);
	Renderer r(fb);
	r.draw_triangle(tri, {255, 255, 255});

	int lit = 0;
	for (int y = 0; y < fb.height(); y++)
		for (int x = 0; x < fb.width(); x++)
			if (fb.color_at(x, y).r > 0) lit++;
	CHECK(lit > 5000 && lit < 5200);

	CHECK(fb.color_at(20, 20).r == 255);    // inside
	CHECK(fb.color_at(100, 100).r == 0);    // outside the hypotenuse
	CHECK(fb.color_at(0, 0).r == 0);        // outside entirely

	// Reversed winding is culled by default, drawn when culling is off.
	const ScreenTriangle flipped = {tri.a, tri.c, tri.b};
	Framebuffer fb2(200, 200);
	Renderer r2(fb2);
	r2.draw_triangle(flipped, {255, 255, 255});
	CHECK(fb2.color_at(20, 20).r == 0);

	r2.set_backface_culling(false);
	r2.draw_triangle(flipped, {255, 255, 255});
	CHECK(fb2.color_at(20, 20).r == 255);

	// Degenerate: three collinear points fill nothing.
	Framebuffer fb3(200, 200);
	Renderer r3(fb3);
	r3.set_backface_culling(false);
	r3.draw_triangle({{0, 0, 0}, {50, 50, 0}, {100, 100, 0}}, {255, 255, 255});
	for (int y = 0; y < fb3.height(); y++)
		for (int x = 0; x < fb3.width(); x++)
			if (fb3.color_at(x, y).r != 0) { CHECK(false); return; }

	// Nearer wins regardless of draw order.
	Framebuffer fb4(200, 200);
	Renderer r4(fb4);
	r4.draw_triangle({{10, 10, 1}, {110, 10, 1}, {10, 110, 1}}, {255, 0, 0});
	r4.draw_triangle({{10, 10, 0}, {110, 10, 0}, {10, 110, 0}}, {0, 255, 0});
	CHECK(fb4.color_at(20, 20).r == 255);

	// A face lands inside the framebuffer and keeps its winding through the
	// camera, so a front-facing quad survives culling.
	const std::string path = "tests/.tmp_quad.obj";
	{
		std::ofstream out(path);
		out << "v -0.5 -0.5 0\nv 0.5 -0.5 0\nv 0.5 0.5 0\nv -0.5 0.5 0\n"
		       "f 1 2 3\nf 1 3 4\n";
	}
	const Mesh quad(path);
	std::remove(path.c_str());
	CHECK(quad.face_count() == 2);

	Framebuffer fb5(100, 100);
	Renderer r5(fb5);
	const Camera cam({0, 0, 5}, {0, 0, 0}, {0, 1, 0});
	const ScreenTriangle st = r5.project_face(quad, 0, cam);
	CHECK(st.a.x > 0.0f && st.a.x < 100.0f);
	CHECK(st.a.y > 0.0f && st.a.y < 100.0f);

	r5.draw_mesh(quad, cam);
	CHECK(fb5.color_at(50, 50).r + fb5.color_at(50, 50).g + fb5.color_at(50, 50).b > 0);
	CHECK(fb5.color_at(1, 1).r + fb5.color_at(1, 1).g + fb5.color_at(1, 1).b == 0);
}
