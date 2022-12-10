precision mediump float;

varying vec3 v_color;

void main()
{
	// Color
	vec4 color = vec4(v_color, 1.0);

	// Predefined
	gl_FragColor = color;
}
