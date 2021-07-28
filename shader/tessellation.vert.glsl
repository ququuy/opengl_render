// OpenGL 4.0
#version 400

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Texture;

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Light Source - Directional
uniform vec4 u_Light_Direction = vec4(0.2f, -1.0f, -0.2f, 0.0f);

// Output to Control Shader
out vec4 ctrl_Position;
out vec4 ctrl_Texture;
out vec4 ctrl_Light_Direction;

void main() {
	//----------------------------------------------
	// Output to Control Shader
	//----------------------------------------------
	// Control Position
	ctrl_Position = vert_Position;

	// Control Texture
	ctrl_Texture = vert_Texture;

	// Control Light Position
	ctrl_Light_Direction = normalize(u_Light_Direction);
}
