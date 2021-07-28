#ifndef GEOMETRY_H
#define GEOMETRY_H

// System Headers
#include <iostream>
#include <vector>

// OpenGL Headers
#if defined(_WIN32)
	#include <GL/glew.h>
	#if defined(GLEW_EGL)
		#include <GL/eglew.h>
	#elif defined(GLEW_OSMESA)
		#define GLAPI extern
		#include <GL/osmesa.h>
	#elif defined(_WIN32)
		#include <GL/wglew.h>
	#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
		#include <GL/glxew.h>
	#endif

	// OpenGL Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
	#include <OpenGL/gl3.h>
#elif defined(__linux__)
	// GLEW Headers
	#include <GL/glew.h>
	#include <GL/gl.h>

	// GLFW Headers
	#define GLFW_INCLUDE_GLCOREARB
	#include <GLFW/glfw3.h>
#endif

// GLM Headers
#include "glm/glm.hpp"

// GLM GTX Extensions (Experimental)
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


// --------------------------------------------------------------------------------
// Create Blade of Grass - Positions, Normals, Colours
void createBlade(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create Ground - Positions, Normals, Colours
void createGround(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);

// --------------------------------------------------------------------------------
// Create River - Positions, Normals
void createRiver(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes);





// Create Quads with Positions and Normals
void createQuads(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes, int X, int Y);

float* DiamondSquare(int X, int Y);

glm::vec3* generateNormals(const float *height, float scale, int X, int Y);

float uniform();


// --------------------------------------------------------------------------------
#endif // GEOMETRY_H