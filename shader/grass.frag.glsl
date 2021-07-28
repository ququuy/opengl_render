// OpenGL 4.0
#version 400

// Input to Fragment Shader
in vec4 frag_Position;
in vec4 frag_Normal;
in vec4 frag_Colour;
in vec4 frag_Light_Direction;

// Light Source
uniform vec4 Ia = vec4(0.6f, 0.6f, 0.6f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Materials
uniform vec4 Ka = vec4(0.1f, 0.1f, 0.1f, 1.0f);
uniform vec4 Kd = vec4(0.6f, 0.6f, 0.6f, 1.0f);
uniform vec4 Ks = vec4(0.3f, 0.3f, 0.3f, 1.0f);
uniform float a = 2.0;

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	//----------------------------------------------
	// Phong Reflection Model
	//----------------------------------------------

	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l = normalize(-frag_Light_Direction);

	// Surface Normal (normalised)
	vec4 n = normalize(frag_Normal);

	// Reflected Vector
	vec4 r = reflect(-l, n);

	// View Vector
	vec4 v = normalize(-frag_Position);

	// ---------- Calculate Terms ----------
	// Ambient Term
	vec4 Ta = Ka * Ia * frag_Colour;

	// Diffuse Term
	vec4 Td = Kd * max(dot(l, n), 0.0) * Id * frag_Colour;

	// Specular Term
	vec4 Ts = Ks * pow((max(dot(r, v), 0.0)), a) * Is * frag_Colour;

	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = Ta + Td + Ts;
}