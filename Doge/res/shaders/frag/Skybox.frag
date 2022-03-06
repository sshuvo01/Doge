#version 330 core

in vec3 v_TexDir;

uniform samplerCube u_SkyboxTexture;

out vec4 fragColor;

void main()
{
	fragColor = texture(u_SkyboxTexture, v_TexDir);
}
