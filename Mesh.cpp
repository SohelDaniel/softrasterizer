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
			// Reading an int stops at '/', so a throwaway string eats the
			// "/uv/normal" remainder of each group.
			Face f;
			std::string skip1, skip2;
			iss >> tag >> f[0] >> skip1 >> f[1] >> skip2 >> f[2];

			// .obj counts vertices from 1, std::vector from 0.
			f[0] -= 1;
			f[1] -= 1;
			f[2] -= 1;
			m_faces.push_back(f);
		}
	}
}
