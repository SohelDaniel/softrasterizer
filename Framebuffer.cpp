
#include "Framebuffer.h"

#include <algorithm>
#include <fstream>

namespace {

void put_u16(std::ofstream& out, std::uint16_t value) {
	const char bytes[2] = {static_cast<char>(value & 0xFF),
	                       static_cast<char>((value >> 8) & 0xFF)};
	out.write(bytes, 2);
}

// 18-byte uncompressed TGA header. datatype 2 = BGR, 3 = greyscale.
void write_tga_header(std::ofstream& out, int width, int height, int bits_per_pixel) {
	const char zero = 0;
	out.put(0);                                            // id length
	out.put(0);                                            // no colour map
	out.put(bits_per_pixel == 8 ? 3 : 2);                  // datatype
	for (int i = 0; i < 5; i++) out.put(zero);             // colour map spec
	put_u16(out, 0);                                       // x origin
	put_u16(out, 0);                                       // y origin
	put_u16(out, static_cast<std::uint16_t>(width));
	put_u16(out, static_cast<std::uint16_t>(height));
	out.put(static_cast<char>(bits_per_pixel));
	out.put(0);                                            // origin bottom-left
}

}  // namespace

Framebuffer::Framebuffer(int width, int height)
	: m_width(width), m_height(height),
	  m_color(static_cast<std::size_t>(width) * height),
	  m_depth(static_cast<std::size_t>(width) * height, kFarthest) {}

void Framebuffer::clear(Color c) {
	std::fill(m_color.begin(), m_color.end(), c);
	std::fill(m_depth.begin(), m_depth.end(), kFarthest);
}

bool Framebuffer::set_if_nearer(int x, int y, float z, Color c) {
	if (!in_bounds(x, y)) return false;

	const std::size_t i = static_cast<std::size_t>(y) * m_width + x;
	if (z <= m_depth[i]) return false;

	m_depth[i] = z;
	m_color[i] = c;
	return true;
}

Color Framebuffer::color_at(int x, int y) const {
	return m_color[static_cast<std::size_t>(y) * m_width + x];
}

float Framebuffer::depth_at(int x, int y) const {
	return m_depth[static_cast<std::size_t>(y) * m_width + x];
}

bool Framebuffer::write_tga(const std::string& path) const {
	std::ofstream out(path, std::ios::binary);
	if (!out) return false;

	write_tga_header(out, m_width, m_height, 24);
	for (const Color& c : m_color) {
		const char bgr[3] = {static_cast<char>(c.b),
		                     static_cast<char>(c.g),
		                     static_cast<char>(c.r)};
		out.write(bgr, 3);
	}
	return static_cast<bool>(out);
}

bool Framebuffer::write_depth_tga(const std::string& path) const {
	std::ofstream out(path, std::ios::binary);
	if (!out) return false;

	// Scale to the range actually used, so the image reads at any camera distance.
	float zmin = 0.0f;
	float zmax = 0.0f;
	bool any = false;
	for (float z : m_depth) {
		if (z == kFarthest) continue;
		if (!any) { zmin = zmax = z; any = true; continue; }
		zmin = std::min(zmin, z);
		zmax = std::max(zmax, z);
	}

	write_tga_header(out, m_width, m_height, 8);
	const float span = zmax - zmin;
	for (float z : m_depth) {
		int shade = 0;
		if (any && span > 0.0f && z != kFarthest) {
			shade = static_cast<int>((z - zmin) / span * 255.0f);
			shade = std::clamp(shade, 0, 255);
		}
		out.put(static_cast<char>(shade));
	}
	return static_cast<bool>(out);
}
