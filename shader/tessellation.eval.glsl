// OpenGL 4.0
#version 400

// layout (quads, equal_spacing, ccw) in;
layout (quads, fractional_odd_spacing, ccw) in;
// layout (quads, fractional_even_spacing, ccw) in;

// Input from Evaluation Shader
in vec4 eval_Position[];
in vec4 eval_Texture[];
in vec4 eval_Light_Direction[];

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Output to Fragment Shader
out vec4 frag_Position;
out vec4 frag_Texture;
out vec4 frag_Light_Direction;

out float frag_Height;

// Scale
uniform float u_Height_Scale;

// Textures
uniform sampler2D u_Height_Map;
uniform sampler2D u_Normal_Map;

void main() {
	//----------------------------------------------
	// Quad - Terrain
	//----------------------------------------------

	// Texture
	vec3 texture_a = mix(eval_Texture[0].xyz, eval_Texture[1].xyz, gl_TessCoord.x);
	vec3 texture_b = mix(eval_Texture[3].xyz, eval_Texture[2].xyz, gl_TessCoord.x);
	vec3 texture_uv = mix(texture_a, texture_b, gl_TessCoord.y);

	// Position
	vec3 pos_a = mix(eval_Position[0].xyz, eval_Position[1].xyz, gl_TessCoord.x);
	vec3 pos_b = mix(eval_Position[3].xyz, eval_Position[2].xyz, gl_TessCoord.x);
	vec3 position = mix(pos_a, pos_b, gl_TessCoord.y);

	// Adjust height
	position.y += texture(u_Height_Map, texture_uv.xy).r * u_Height_Scale;
	//frag_Height = (u_Model * vec4(position, 1.0)).y;
	frag_Height = position.y;

	//----------------------------------------------
	// Output to Fragment Shader
	//----------------------------------------------
	// Frag Position
	frag_Position = vec4(position, 1.0f);

	// Frag Texture
	frag_Texture = vec4(texture_uv, 0.0f);

	// Frag Light Direction
	frag_Light_Direction = eval_Light_Direction[0];

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
}