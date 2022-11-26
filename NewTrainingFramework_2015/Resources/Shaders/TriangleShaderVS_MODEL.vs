attribute vec3 a_color;

varying vec3 v_color;
attribute vec2 a_uv;

uniform mat4 u_rotZ;
uniform mat4 u_view;
uniform mat4 u_persp;

varying vec2 v_uv;

void main()
{
	// Position
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position =  u_persp * u_view *u_rotZ * posL;
	v_uv = a_uv;
}
