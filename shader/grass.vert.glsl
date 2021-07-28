// OpenGL 4.0
#version 400

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec4 vert_Colour;

//----------------------------------------------
// Individual Rendering
//----------------------------------------------
// Uniform Model Matrix
// uniform mat4 u_Model;

//----------------------------------------------
// Instanced - Calculate Position
//----------------------------------------------
// // Grass size
// uniform int u_GrassX = 100;
// uniform int u_GrassZ = 100;

//----------------------------------------------
// Instanced - Uniform Values
//----------------------------------------------
// // Instanced Uniform Model Matrix
// uniform mat4 u_Model[200];

//----------------------------------------------
// Instanced - Vertex Attributes
//----------------------------------------------
// // Vertex Attributes
layout(location = 6) in mat4 inst_Model;

uniform mat4 g_Matrix;


//----------------------------------------------
// Transform Matrices
uniform mat4 u_View;
uniform mat4 u_Projection;

// Light Source - Directional
// uniform vec4 u_Light_Direction = vec4(0.0f, -0.5f, -1.0f, 0.0f);
uniform vec4 u_Light_Direction =vec4(0.0f, -0.5f, -0.5f, 0.0f);

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Normal;
out vec4 frag_Colour;
out vec4 frag_Light_Direction;

//----------------------------------------------
// Instanced - Vertex Buffer Object
//----------------------------------------------
void main() {
	// Model Matrix
	mat4 model;

	//----------------------------------------------
	// Individual Rendering
	//----------------------------------------------
	// model = u_Model;

	//----------------------------------------------
	// Calculate Transform
	//----------------------------------------------
	// float x = ((gl_InstanceID % u_GrassX) / float(u_GrassX)) * 2.0f - 1.0f;
	// float z = ((gl_InstanceID / u_GrassX) / float(u_GrassZ)) * 2.0f - 1.0f;
	// float theta = gl_InstanceID * 7.0f;

	// // Translation matrix
	// mat4 translation = mat4(1,   0,   0,   0,
	// 						0,   1,   0,   0,
	// 						0,   0,   1,   0,
	// 						x,   0,   z,   1);

	// // Rotation matrix
	// mat4 rotation = mat4(cos(theta), 0,          sin(theta), 0,
	// 					 0,          1,          0,          0,
	// 					-sin(theta), 0,          cos(theta), 0,
	// 					 0,          0,          0,          1);

	// // Scale matrix
	// mat4 scale = mat4(0.005, 0,     0,     0,
	// 				  0,     0.005, 0,     0,
	// 				  0,     0,     0.005, 0,
	// 				  0,     0,     0,     1);

	// // Model Matrix
	// model = translation * rotation * scale;

	//----------------------------------------------
	// Uniform Variables
	//----------------------------------------------
	// model = u_Model[gl_InstanceID];

	//----------------------------------------------
	// Instance Attributes
	//----------------------------------------------
	 model = g_Matrix * inst_Model;

	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Position
	frag_Position = u_View * model * vert_Position;

	// Normal
	frag_Normal = u_View * model * vert_Normal;

	// Colour
	frag_Colour = vert_Colour;

	// Light Direction
	frag_Light_Direction = u_View * normalize(u_Light_Direction);

	//----------------------------------------------
	// Fragment Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * model * vert_Position;
}
