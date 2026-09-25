
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <string>
#include <vector>

struct Color {
	std::uint8_t r = 0;
	std::uint8_t g = 0;
	std::uint8_t b = 0;
};

// The render target: one colour buffer and one depth buffer, same size.
//
// They are kept together because they must always be written together -- a
// pixel's colour and the depth recorded for it have to come from the same
// triangle, or they drift apart. `set_if_nearer` is the only way to write,
// which makes that mistake impossible to express.
//
// The origin is bottom-left, so y increases upward, matching the maths rather
// than the screen. write_tga handles the conversion.
class Framebuffer {
public:
	Framebuffer(int width, int height);

	int width() const  { return m_width; }
	int height() const { return m_height; }

	bool in_bounds(int x, int y) const {
		return x >= 0 && y >= 0 && x < m_width && y < m_height;
	}

	// Resets colour to `c` and depth to "infinitely far".
	void clear(Color c = {});

	// Writes colour and depth only if `z` is nearer than what is already
	// recorded. Larger z means nearer. Returns true when the pixel was written.
	bool set_if_nearer(int x, int y, float z, Color c);

	Color color_at(int x, int y) const;
	float depth_at(int x, int y) const;

	// Both return false if the file could not be written.
	bool write_tga(const std::string& path) const;

	// Depth as 8-bit greyscale, auto-scaled between the nearest and farthest
	// pixel that was actually drawn. Untouched pixels stay black.
	bool write_depth_tga(const std::string& path) const;

	static constexpr float kFarthest = -1e30f;

private:
	int m_width;
	int m_height;
	std::vector<Color> m_color;
	std::vector<float> m_depth;
};

#endif
