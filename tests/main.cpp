#include "test.h"

void test_vec3();
void test_framebuffer();
void test_mesh();
void test_renderer();

int main() {
	test_vec3();
	test_framebuffer();
	test_mesh();
	test_renderer();
	return test::summary();
}
