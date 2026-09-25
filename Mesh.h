/*This module needs to take a .obj file and turn it into indexed geometry*/
//In an obj file we have two tyes of lines :
//EX: "f 5/6/7 8/9/10 11/12/13" which are indices of vertices ,
//and "v 0.80433 0.9844 0.12356" which are vertices spaning ranges [-1,1]
#ifndef MESH_H
#define MESH_H
#include "Vec3.h"
#include <vector>

struct Face{
	int faces[3];
	int& operator[](int i) {
		return faces[i];
	}
	const int& operator[](int i) const{
		return faces[i];
	}
};
class Mesh {
public:
	explicit Mesh(std::string& filename);
	//return vertices size.
	int vertex_count(int i) const {
		return m_vertices.size();
	}
	//return triangles sizes.
	int face_count(int i) const {
		return m_faces.size();
	}

	const Vec3& vertex (int i) const{
		return m_vertices[i];
	}

	const Face& face(int i) const{
		return m_faces[i];
	}

	//return a corner in a triangle
	const Vec3 corner(int i,int j) const {
		return m_vertices[m_faces[i][j]];
	}
private:
	std::vector<Vec3> m_vertices;
	std::vector<Face> m_faces;
};

#endif
