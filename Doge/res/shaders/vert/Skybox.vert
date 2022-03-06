#version 330 core

layout(location = 0) in vec3 vertex;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_TexDir;

void main()
{
	v_TexDir = -vertex;
	vec4 temp = u_Projection * u_View  * vec4(vertex, 1.0);

	gl_Position = temp.xyww;
}