#include "test.h"

void test_vec3();
void test_matrix();
void test_camera();
void test_framebuffer();
void test_mesh();
void test_renderer();

int main() {
	test_vec3();
	test_matrix();
	test_camera();
	test_framebuffer();
	test_mesh();
	test_renderer();
	return test::summary();
}
