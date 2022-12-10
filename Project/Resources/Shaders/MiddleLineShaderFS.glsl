precision mediump float;

// Constants
varying vec3 v_color;

void main()
{
	// Predefined
	gl_FragColor = vec4(v_color, 1.0);
}
