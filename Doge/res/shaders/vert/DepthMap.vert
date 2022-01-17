#version 330 core

layout (location = 0) in vec3 a_Vertex;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in vec2 a_Tangent;
layout (location = 4) in vec2 a_Bitangent;
layout (location = 5) in mat4 a_ModelInstance;

uniform mat4 u_LightSpaceMat;

void main()
{
	gl_Position = u_LightSpaceMat * a_ModelInstance * vec4(a_Vertex, 1.0);
}