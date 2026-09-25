#include "test.h"

#include <cstdio>
#include <fstream>

#include "Framebuffer.h"

void test_framebuffer() {
	Framebuffer fb(4, 3);
	CHECK(fb.width() == 4);
	CHECK(fb.height() == 3);

	CHECK(fb.in_bounds(0, 0));
	CHECK(fb.in_bounds(3, 2));
	CHECK(!fb.in_bounds(4, 0));
	CHECK(!fb.in_bounds(-1, 0));

	// Out of bounds is ignored, not a crash.
	CHECK(!fb.set_if_nearer(99, 99, 1.0f, {255, 0, 0}));

	CHECK(fb.set_if_nearer(1, 1, 0.0f, {255, 0, 0}));
	CHECK(fb.color_at(1, 1).r == 255);

	// Farther loses, nearer wins, equal loses.
	CHECK(!fb.set_if_nearer(1, 1, -1.0f, {0, 255, 0}));
	CHECK(fb.color_at(1, 1).r == 255);
	CHECK(!fb.set_if_nearer(1, 1, 0.0f, {0, 255, 0}));
	CHECK(fb.color_at(1, 1).r == 255);
	CHECK(fb.set_if_nearer(1, 1, 1.0f, {0, 0, 255}));
	CHECK(fb.color_at(1, 1).b == 255);
	CHECK_NEAR(fb.depth_at(1, 1), 1.0);

	fb.clear();
	CHECK(fb.color_at(1, 1).b == 0);
	CHECK(fb.depth_at(1, 1) == Framebuffer::kFarthest);

	// 18-byte header + w*h*3 bytes of BGR.
	const std::string path = "tests/.tmp_fb.tga";
	CHECK(fb.write_tga(path));
	std::ifstream in(path, std::ios::binary | std::ios::ate);
	CHECK(in && in.tellg() == 18 + 4 * 3 * 3);
	in.close();
	std::remove(path.c_str());
}
