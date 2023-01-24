// Global variables that change per vertex
attribute vec3 a_posL;
attribute vec3 a_color;

// Interpolated in fragment shader
varying vec3 v_color;

// Constant to all points
uniform mat4 u_rotation;
uniform mat4 u_rotZ;
uniform mat4 u_view;
uniform mat4 u_persp;

void main()
{
	// Predefined
	gl_Position = u_persp * u_view * u_rotZ * u_rotation * vec4(a_posL, 1.0);

	// Color
	v_color = a_color;
}