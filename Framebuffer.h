
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

// Render target: colour and depth, same dimensions. Kept together because a
// pixel's colour and its depth must be written as one; set_if_nearer is the
// only writer, so they cannot fall out of step.
//
// Origin is bottom-left (y up). write_tga handles the conversion.
class Framebuffer {
public:
	Framebuffer(int width, int height);

	int width() const  { return m_width; }
	int height() const { return m_height; }

	bool in_bounds(int x, int y) const {
		return x >= 0 && y >= 0 && x < m_width && y < m_height;
	}

	// Colour to `c`, depth to kFarthest.
	void clear(Color c = {});

	// Writes only if z is nearer than what is stored. Larger z is nearer.
	bool set_if_nearer(int x, int y, float z, Color c);

	Color color_at(int x, int y) const;
	float depth_at(int x, int y) const;

	// Both return false on write failure.
	bool write_tga(const std::string& path) const;

	// Depth as 8-bit greyscale, scaled to the range actually drawn.
	bool write_depth_tga(const std::string& path) const;

	static constexpr float kFarthest = -1e30f;

private:
	int m_width;
	int m_height;
	std::vector<Color> m_color;
	std::vector<float> m_depth;
};

#endif
