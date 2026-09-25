#include "test.h"

void test_vec3();
void test_framebuffer();

int main() {
	test_vec3();
	test_framebuffer();
	return test::summary();
}
