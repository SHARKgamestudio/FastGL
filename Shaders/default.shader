#shader vert
#version 330 core
in vec2 position;
void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
}

#shader frag
#version 330 core
out vec4 outColor;

uniform float u_R;
void main()
{
	outColor = vec4(u_R, 0, 0, 1);
}