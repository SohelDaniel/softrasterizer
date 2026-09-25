//This module does the main raterisation , it turns geometry into pixels.
#ifndef RENDERER_H
#define RENDERER_H
#include "Framebuffer.h"
#include "Mesh.h"

struct ScreenVertex {
	float x = 0.0f;
	float y = 0.0f;
	float depth = 0.0f;
};

// A face that has been through the camera and is ready to fill.
struct ScreenTriangle {
	ScreenVertex a;
	ScreenVertex b;
	ScreenVertex c;
};





class Renderer{

public:
private:
};

#endif
