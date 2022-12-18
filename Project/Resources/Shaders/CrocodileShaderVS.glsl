// Global variables that change per vertex
attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;

// Interpolated in fragment shader
varying vec3 v_color;
varying vec2 v_uv;

// Constant to all points
uniform mat4 u_rotation;
uniform mat4 u_rotZ;
uniform mat4 u_view;
uniform mat4 u_persp;
uniform mat4 u_scalation;
uniform sampler2D u_texture;

void main()
{
	// Predefined
	gl_Position = u_persp * u_view * u_rotation * u_scalation * vec4(a_posL, 1.0);

	// Color
	v_color = a_color;

	// Texture
	v_uv = a_uv;
}