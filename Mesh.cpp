#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
Mesh::Mesh(std::string& filename){
	std::ifstream file(filename);
	if(!file){
		throw std::runtime_error("Could not open file: " + filename +"\n"std::endl;
	}
	std::string line;
	while(std::getline(file,line)){
		std::istringstream iss(line);

		if(line.compare(0,2,"v ") == 0){
			std::string tag;
			float a,b,c;
			iss>>tag>>a>>b>>c;
			Vec3 temp = {a,b,c};
			vertices.push_back(temp);
		}
		else if(line.compare(0,2,"f ") == 0){
			std::string tag,t1,t2;
			int a,b,c;
			iss>>tag>>a>>b>>c;
			Triangle temp = {a,b,c};
			triangles.push_back(temp);
		}
	}
	file.close();

}
