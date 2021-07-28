// OpenGL 4.0
#version 400
// Reference:
// https://github.com/damdoy/opengl_examples/tree/master/water
in vec4 frag_Position;
in vec4 frag_Normal;
in vec4 frag_Colour;
in vec2 frag_uv;
in vec4 r_Position;
in vec4 view_Position;
in vec4 frag_Light_Direction;
in vec4 frag_Light_Position;

uniform float time;
uniform mat4 u_Projection;
uniform vec4 camera_Position;
uniform float a = 128;
uniform sampler2D u_Reflection_Map;


// Output from Fragment Shader
out vec4 pixel_Colour;


float generate_wave(float x, float y){
    float wave = 0.01*sin( dot(normalize(vec2(1,0)), vec2(x, y)) *128+time);
    wave += 0.01*sin( dot(normalize(vec2(15,1)), vec2(x, y)) *128+time);
    wave += 0.01*sin( dot(normalize(vec2(10,-1)), vec2(x, y)) *256+time*1.5);
    wave += 0.01*sin( dot(normalize(vec2(3,1)), vec2(x, y)) *256+time*1.5);
    wave += 0.02*sin( dot(normalize(vec2(6,-1)), vec2(x, y)) *64+time*0.8);
    wave += 0.015*sin( dot(normalize(vec2(8,1)), vec2(x, y)) *128+time*0.7);
    return wave/3;
}


void main () {
    float wave = generate_wave(frag_uv[0], frag_uv[1]);

    //float dt = 0.01;
    float dt = 0.02;
    vec3 pos_before_x = vec3(frag_uv.x-dt, generate_wave(frag_uv.x-dt, frag_uv.y), frag_uv.y);
    vec3 pos_after_x = vec3(frag_uv.x+dt, generate_wave(frag_uv.x+dt, frag_uv.y), frag_uv.y);
    vec3 pos_before_y = vec3(frag_uv.x, generate_wave(frag_uv.x, frag_uv.y-dt), frag_uv.y-dt);
    vec3 pos_after_y = vec3(frag_uv.x, generate_wave(frag_uv.x, frag_uv.y+dt), frag_uv.y+dt);

    vec3 normal_wave = normalize(cross( pos_after_x-pos_before_x, pos_after_y-pos_before_y));

	// ---------- Calculate Vectors ----------
	// Direction to Light (normalised)
	vec4 l = normalize(-frag_Light_Direction);

	// Surface Normal (normalised)
	vec4 n = vec4(normal_wave, 1.0);

	// Reflected Vector
	vec4 r = reflect(-l, -n);

	// View Vector
	vec4 v = normalize(camera_Position - frag_Position);

	// ---------- Calculate Terms ----------
	float Td = max(dot(l, n), 0.0) / (1 + pow(length(frag_Light_Position - frag_Position), -0.5));// * vec4(1.0, 1.0, 1.0, 0.0);
	float Ts = clamp(pow((max(dot(r, v), 0.0)), a), 0.0, 1.0);

	// --------- reflected color ----------
	vec4 proj_Position = r_Position;
	vec2 screen_coord = proj_Position.xy*0.5/proj_Position.w + vec2(0.5, 0.5);
	screen_coord += vec2(wave, wave);
	vec3 color_reflect = texture(u_Reflection_Map, screen_coord).rgb;

	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour.rgb = 0.5 * color_reflect + 0.5 * Td + 0.8 * Ts;
	pixel_Colour.a = 1.0;
}