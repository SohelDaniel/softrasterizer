/*This module needs to take a .obj file and turn it into indexed geometry*/
//In an obj file we have two tyes of lines :
//EX: "f 5/6/7 8/9/10 11/12/13" which are indices of vertices ,
//and "v 0.80433 0.9844 0.12356" which are vertices spaning ranges [-1,1]
#ifndef MESH_H
#define MESH_H
#include "Vec3.h"
#include <vector>

struct Triangle{
	int triangles[3];
	int& operator[](int i) {
		return triangles[i];
	}
	const int& operator[](int i) const{
		return triangles[i];
	}
};
class Mesh {
public:
	explicit Mesh(std::string& filename);
	int n_vertices(int i) const {
		return vertices.size();
	}
	int n_triangles(int i) const {
		return triangles.size();
	}
	const Vec3& vertex (int i) const{
		return vertices[i];
	}
	const Triangle& triangle(int i) const{
		return triangles[i];
	}

	//return a corner in a triangle
	const Vec3 corner(int i,int j) const {
		return vertices[triangles[i][j]];
	}


private:
	std::vector<Vec3> vertices;
	std::vector<Triangle> triangles;


};

#endif
