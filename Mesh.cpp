#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh::Mesh(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Mesh: could not open " + filename);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string tag;

		if (line.compare(0, 2, "v ") == 0) {
			Vec3 v;
			iss >> tag >> v.x >> v.y >> v.z;
			m_vertices.push_back(v);
		} else if (line.compare(0, 2, "f ") == 0) {
			// A corner is "v", "v/vt", "v//vn" or "v/vt/vn". stoi reads the
			// leading index and stops at the slash, so all four forms work.
			// .obj counts vertices from 1, std::vector from 0.
			Face f;
			iss >> tag;
			int corners = 0;
			std::string group;
			while (corners < 3 && iss >> group) {
				f[corners++] = std::stoi(group) - 1;
			}
			if (corners == 3) m_faces.push_back(f);
		}
	}
}
