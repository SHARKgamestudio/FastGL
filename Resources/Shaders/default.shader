#shader vert
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_Mvp;

out vec2 v_TexCoord;

void main()
{
	gl_Position = u_Mvp * vec4(position, 0.0, 1.0);
	v_TexCoord = texCoord;
}

#shader frag
#version 330 core
layout(location = 0) out vec4 outColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	outColor = texture(u_Texture, v_TexCoord);
}