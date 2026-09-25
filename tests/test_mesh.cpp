#include "test.h"

#include <cstdio>
#include <fstream>
#include <stdexcept>

#include "Mesh.h"

namespace {

std::string write_temp_obj() {
	const std::string path = "tests/.tmp_mesh.obj";
	std::ofstream out(path);
	out << "# comment line\n"
	       "v 0 0 0\n"
	       "v 1 0 0\n"
	       "v 0 1 0\n"
	       "vt 0.5 0.5\n"
	       "vn 0 0 1\n"
	       "f 1/1/1 2/1/1 3/1/1\n"
	       "f 3/1/1 2/1/1 1/1/1\n"
	       "f 1 2 3\n"
	       "f 1//1 2//1 3//1\n"
	       "f 1/1 2/1 3/1\n";
	return path;
}

}  // namespace

void test_mesh() {
	const std::string path = write_temp_obj();
	const Mesh mesh(path);

	// "vt"/"vn" start with 'v' but not "v ", so they must not become vertices.
	CHECK(mesh.vertex_count() == 3);

	// All four corner spellings parse: v, v/vt, v//vn, v/vt/vn.
	CHECK(mesh.face_count() == 5);
	for (int i = 2; i < mesh.face_count(); i++) {
		CHECK(mesh.face(i)[0] == 0);
		CHECK(mesh.face(i)[2] == 2);
	}

	// Indices converted from 1-based to 0-based.
	CHECK(mesh.face(0)[0] == 0);
	CHECK(mesh.face(0)[2] == 2);
	CHECK(mesh.face(1)[0] == 2);

	CHECK_NEAR(mesh.vertex(1).x, 1.0);
	CHECK_NEAR(mesh.corner(0, 2).y, 1.0);
	CHECK_NEAR(mesh.corner(1, 0).y, 1.0);

	std::remove(path.c_str());

	bool threw = false;
	try { Mesh missing("tests/.does_not_exist.obj"); }
	catch (const std::runtime_error&) { threw = true; }
	CHECK(threw);
}
