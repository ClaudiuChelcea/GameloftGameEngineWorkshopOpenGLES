// Globals
attribute vec3 a_posL;
attribute vec3 a_color;

// Constants
varying vec3 v_color;

void main()
{
	// Position
	gl_Position = vec4(a_posL, 1.0);

	// Send color
	v_color = a_color;
}
   