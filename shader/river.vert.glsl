// OpenGL 4.0
#version 400

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_Normal;
in vec2 tex_UV;
// in vec4 vert_Colour;

//----------------------------------------------
// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform mat4 r_View;

// Light Source - Directional
uniform vec4 u_Light_Direction = vec4(0.0f, -0.5f, -0.5f, 0.0f);
uniform vec4 u_Light_Position = vec4(10.0f, 30.0f, 10.0f, 0.0f);

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Normal;
out vec4 frag_Colour;
out vec4 frag_Light_Direction;
out vec4 frag_Light_Position;

out vec2 frag_uv;
out vec4 r_Position;
out vec4 view_Position;

//----------------------------------------------
// Instanced - Vertex Buffer Object
//----------------------------------------------
void main() {
	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Position
	frag_Position = u_Model * vert_Position;

	// Normal
	frag_Normal = u_Model * vert_Normal;

	// Colour
	// frag_Colour = vert_Colour;
	frag_Colour = vec4(0.7, 0.7, 0.5, 1.0);

	// Light Direction
	frag_Light_Direction = normalize(u_Light_Direction);
	frag_Light_Position = u_Light_Position;

	frag_uv = tex_UV;

	r_Position = u_Projection * r_View * u_Model * vert_Position;

	view_Position = u_View * u_Model * vert_Position;


	//----------------------------------------------
	// Fragment Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vert_Position;
}
