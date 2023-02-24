precision mediump float;

// Constants
uniform sampler2D u_texture;
varying vec2 v_uv;

void main()
{
	// Predefined
	vec4 color = texture2D(u_texture, v_uv);
	if(color.a < 0.2) { // Transparent
		discard;
	}
	
	gl_FragColor = color;
}
