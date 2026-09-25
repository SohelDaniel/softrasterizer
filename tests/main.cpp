#include "test.h"

void test_vec3();
void test_framebuffer();
void test_mesh();

int main() {
	test_vec3();
	test_framebuffer();
	test_mesh();
	return test::summary();
}
