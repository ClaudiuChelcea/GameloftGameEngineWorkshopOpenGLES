// Global variables that change per vertex
attribute vec3 a_posL;
attribute vec3 a_color;

// Interpolated in fragment shader
varying vec3 v_color;

// Constant to all points
uniform mat4 a_rotation;

void main()
{
	// Predefined
	gl_Position = a_rotation * vec4(a_posL, 1.0);

	// Color
	v_color = a_color;
}