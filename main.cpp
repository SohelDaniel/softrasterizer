#include <iostream>
#include <string>

#include "Camera.h"
#include "Framebuffer.h"
#include "Mesh.h"
#include "Renderer.h"

int main(int argc, char** argv) {
	const std::string model_path = argc > 1 ? argv[1] : "assets/model.obj";
	constexpr int width = 800;
	constexpr int height = 800;

	try {
		const Mesh mesh(model_path);
		std::cout << model_path << ": " << mesh.vertex_count() << " vertices, "
		          << mesh.face_count() << " faces\n";

		const Camera camera({0, 0, 5}, {0, 0, 0}, {0, 1, 0});

		Framebuffer target(width, height);
		Renderer renderer(target);
		renderer.draw_mesh(mesh, camera);

		if (!target.write_tga("framebuffer.tga") ||
		    !target.write_depth_tga("zbuffer.tga")) {
			std::cerr << "failed to write output\n";
			return 1;
		}
		std::cout << "wrote framebuffer.tga and zbuffer.tga\n";
	} catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
