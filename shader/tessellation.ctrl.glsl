// OpenGL 4.0
#version 400

// Quads
layout (vertices = 4) out;

// Input to Control Shader
in vec4 ctrl_Position[];
in vec4 ctrl_Texture[];
in vec4 ctrl_Light_Direction[];

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform float u_TessLevelInner1 = 1.0f;
uniform float u_TessLevelInner2 = 1.0f;

uniform float u_TessLevelOuter1 = 1.0f;
uniform float u_TessLevelOuter2 = 1.0f;
uniform float u_TessLevelOuter3 = 1.0f;
uniform float u_TessLevelOuter4 = 1.0f;

// Output from Control Shader
out vec4 eval_Position[];
out vec4 eval_Texture[];
out vec4 eval_Light_Direction[];


float distanceTessLevel(float z0, float z1) {
	// Distance Scaling Factor
	float p = 25;

	// 
	return max(pow(1.0f - z0, p), pow(1.0f - z1, p)) / 1.0f;
}


void main () {
	//----------------------------------------------
	// Output to Tessellation Primitive Generator - Distance Based - Quad
	//----------------------------------------------

	// Vertex Positions (eye space)
	vec4 v0 = u_View * u_Model * ctrl_Position[0];
	vec4 v1 = u_View * u_Model * ctrl_Position[1];
	vec4 v2 = u_View * u_Model * ctrl_Position[2];
	vec4 v3 = u_View * u_Model * ctrl_Position[3];

	// Near & Far Planes (Projection Matrix)
	float zNear = -0.2f;
	float zFar = -50.0f;

	// Vertex Distances
	float z0 = (v0.z - zNear) / (zFar - zNear);
	float z1 = (v1.z - zNear) / (zFar - zNear);
	float z2 = (v2.z - zNear) / (zFar - zNear);
	float z3 = (v3.z - zNear) / (zFar - zNear);

	//----------------------------------------------
	// Calculate Tessellations Levels - Quad
	float max_Tess = 64.0f;

	float outer0 = distanceTessLevel(z0, z3);
	float outer1 = distanceTessLevel(z1, z0);
	float outer2 = distanceTessLevel(z2, z1);
	float outer3 = distanceTessLevel(z3, z2);

	// Calculate inner Tessellation Levels
	float inner1 = max(max(outer0, outer1), max(outer2, outer3));
	float inner2 = max(max(outer0, outer1), max(outer2, outer3));

	//----------------------------------------------
	// Output to Tessellation Primitive Generator - Distance Based
	//----------------------------------------------
	if(gl_InvocationID == 0) {
		// Set Inner Tessellation Level
		gl_TessLevelInner[0] = inner1 * max_Tess;
		gl_TessLevelInner[1] = inner2 * max_Tess;

		// Set Outer Tessellation Level
		gl_TessLevelOuter[0] = outer0 * max_Tess;
		gl_TessLevelOuter[1] = outer1 * max_Tess;
		gl_TessLevelOuter[2] = outer2 * max_Tess;
		gl_TessLevelOuter[3] = outer3 * max_Tess;
	}

	//----------------------------------------------
	// Output to Tessellation Primitive Generator - User Input
	//----------------------------------------------
	// if(gl_InvocationID == 0) {
	// 	// Set Inner Tessellation Level
	// 	gl_TessLevelInner[0] = u_TessLevelInner1;
	// 	gl_TessLevelInner[1] = u_TessLevelInner2;

	// 	// Set Outer Tessellation Level
	// 	gl_TessLevelOuter[0] = u_TessLevelOuter1;
	// 	gl_TessLevelOuter[1] = u_TessLevelOuter2;
	// 	gl_TessLevelOuter[2] = u_TessLevelOuter3;
	// 	gl_TessLevelOuter[3] = u_TessLevelOuter4;
	// }

	//----------------------------------------------
	// Output to Tessellation Evaluation Shader
	//----------------------------------------------

	// Evaluation Position
	eval_Position[gl_InvocationID] = ctrl_Position[gl_InvocationID];

	// Evaluation Texture
	eval_Texture[gl_InvocationID] = ctrl_Texture[gl_InvocationID];

	// Evaluation Light Direction
	eval_Light_Direction[gl_InvocationID] = ctrl_Light_Direction[gl_InvocationID];
}