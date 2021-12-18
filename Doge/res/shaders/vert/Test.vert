#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform vec3 color;

out vec3 col;
out vec2 texCoord;

uniform mat4 u_Model, u_View, u_Projection, u_MVP; 

void main()
{
	col = aColor;
	texCoord = aTexCoord;
    gl_Position = u_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}