#pragma once

//#ifndef SHADER_H
#define SHADER_H

#include "../ew/ewMath/external/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace jeff {
	class Shader {
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath);

		void use();

		void setBool();
		void setInt();
		void setFloat();
	};
}