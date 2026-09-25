#include "Renderer.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace {

// Twice the signed area on the screen plane. Sign gives the winding
// (positive = counter-clockwise = front-facing); magnitude gives the
// barycentric weights.
float signed_area2(const ScreenVertex& a, const ScreenVertex& b, const ScreenVertex& c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

}  // namespace

void Renderer::draw_triangle(const ScreenTriangle& tri, Color color) {
	ScreenVertex a = tri.a;
	ScreenVertex b = tri.b;
	ScreenVertex c = tri.c;

	float area = signed_area2(a, b, c);

	if (m_cull_backfaces) {
		// Also drops slivers covering less than a pixel.
		if (area < 1.0f) return;
	} else {
		if (std::fabs(area) < 1e-6f) return;
		if (area < 0.0f) {
			std::swap(b, c);   // keep the sign tests below meaning "inside"
			area = -area;
		}
	}

	const int min_x = std::max(0, static_cast<int>(std::min({a.x, b.x, c.x})));
	const int max_x = std::min(m_target.width() - 1,
	                           static_cast<int>(std::max({a.x, b.x, c.x})));
	const int min_y = std::max(0, static_cast<int>(std::min({a.y, b.y, c.y})));
	const int max_y = std::min(m_target.height() - 1,
	                           static_cast<int>(std::max({a.y, b.y, c.y})));

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			const ScreenVertex p = {static_cast<float>(x), static_cast<float>(y), 0.0f};

			// Each sub-area swaps one corner for the pixel; all non-negative
			// means inside.
			const float wa = signed_area2(p, b, c);
			const float wb = signed_area2(a, p, c);
			const float wc = signed_area2(a, b, p);
			if (wa < 0.0f || wb < 0.0f || wc < 0.0f) continue;

			// The same ratios interpolate depth across the face.
			const float depth = (wa * a.depth + wb * b.depth + wc * c.depth) / area;

			m_target.set_if_nearer(x, y, depth, color);
		}
	}
}
