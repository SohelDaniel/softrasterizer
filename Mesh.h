// Parses a .obj into indexed geometry.
//   "v 0.80433 0.9844 0.12356"   vertex position, roughly in [-1,1]
//   "f 5/6/7 8/9/10 11/12/13"    face; the first number of each group is the
//                                vertex index, the rest are uv/normal
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "Vec3.h"

// Three indices into the vertex list, not three positions: a vertex shared by
// several faces is stored once, and the faces agree on which one it is.
struct Face {
	int v[3] = {0, 0, 0};

	int&       operator[](int i)       { return v[i]; }
	const int& operator[](int i) const { return v[i]; }
};

class Mesh {
public:
	// Throws std::runtime_error if the file cannot be opened.
	explicit Mesh(const std::string& filename);

	int vertex_count() const { return static_cast<int>(m_vertices.size()); }
	int face_count() const   { return static_cast<int>(m_faces.size()); }

	const Vec3& vertex(int i) const { return m_vertices[i]; }
	const Face& face(int i) const   { return m_faces[i]; }

	// Position of corner c (0..2) of face f.
	Vec3 corner(int f, int c) const { return m_vertices[m_faces[f][c]]; }

private:
	std::vector<Vec3> m_vertices;
	std::vector<Face> m_faces;
};

#endif
