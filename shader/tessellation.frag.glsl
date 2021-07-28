// OpenGL 3.3
#version 400

// Input to Fragment Shader
in vec4 frag_Position;
in vec4 frag_Texture;
in vec4 frag_Light_Direction;

in float frag_Height;

// Textures
uniform sampler2D u_Height_Map;
uniform sampler2D u_Normal_Map;

// Transform Matrices
uniform mat4 u_Model;
uniform mat4 u_View;

// Light Source
//uniform vec4 Ia = vec4(0.1f, 0.1f, 0.1f, 1.0f);
uniform vec4 Ia = vec4(0.6f, 0.6f, 0.6f, 1.0f);
uniform vec4 Id = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 Is = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Material - Grey
uniform vec4 Ka = vec4(0.6, 0.8, 0.6, 1.0);
//uniform vec4 Ka = vec4(0.8, 0.8, 0.8, 1.0);
uniform vec4 Kd = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 Ks = vec4(0.2, 0.2, 0.2, 1.0);
uniform float a = 1.0f;

const vec3 COLOR[3] = vec3[](
    vec3(0.0, 0.0, 1.0), //blue, water
    vec3(0.0, 0.7, 0.0), // green, grass
    vec3(0.70, 0.7, 0.3)); //

// Output from Fragment Shader
out vec4 pixel_Colour;

void main () {
	//----------------------------------------------
	// Normal Calculation - Fragment Shader
	//----------------------------------------------

	vec4 normal = texture(u_Normal_Map, frag_Texture.xy) * 2.0f - vec4(1.0f, 1.0f, 1.0f, 0.0f);

	//----------------------------------------------
	// Phong Reflection Model
	//----------------------------------------------

	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l = normalize(-u_View * frag_Light_Direction);

	// Surface Normal (normalised)
	vec4 n = normalize(u_View * normal);

	// Reflected Vector
	vec4 r = normalize(reflect(-l, n));

	// View Vector
	vec4 v = normalize(-(vec4((u_View * u_Model * frag_Position).xyz, 0.0f)));

	// ---------- Calculate Terms ----------

	float height = 0.0;
	height = frag_Height;
	//height = (height * 2.0 + 0.8);
	height = (height * 2.0 + 1.0);
    float alpha = 0.0;
    int id = 0;
    vec4 _Kd = vec4(0.0);
    // if (height < 0.5) { alpha = height * 2; id = 0; }
    // else { alpha = (height - 0.5) * 2; id = 1; }
    // vec4 _Kd = vec4( (1.0-alpha) * COLOR[id] + alpha * COLOR[id+1] , 1.0);
    if (height < 0.5) {
        _Kd = vec4( (1.0 - 2*height)*COLOR[0] + 2*height*COLOR[1], 1.0);
    } else {
        _Kd = vec4( (1.0 - 2*(height-0.5))*COLOR[1] + 2*(height-0.5)*COLOR[2], 1.0);
    }

	// Ambient Term
	vec4 Ta = Ka * Ia;

	// Diffuse Term
	vec4 Td = _Kd * max(dot(l, n), 0.0) * Id;


	// Specular Term
	vec4 Ts = Ks * pow((max(dot(r, v), 0.0)), a) * Is; 

	pixel_Colour = 0.3 * Ta + Td;// + Ts;
	//pixel_Colour = Td ;
}