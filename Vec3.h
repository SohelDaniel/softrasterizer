//This module is the vector type + all operators ,vectors are the vertexes parsed from the .obj file.
#ifndef VEC3_H
#define VEC3_H
#include <stdexcept>
struct Vec3{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3()  = default;

	Vec3(float x,float y,float z) : x(x), y(y) , z(z) {} 


	float& operator[](int i){
		if(i == 0)return x;
		else if (i == 1) return y;
		else if(i == 2)return z;
		else{
			throw std::out_of_range("Invalid argument");
		}
	}
	const float& operator[](int i) const{
		if(i == 0)return x;
		else if (i == 1) return y;
		else if(i == 2)return z;
		else{
			throw std::out_of_range("Invalid argument");
		}
	}
};
#endif
