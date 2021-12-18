#version 330 core

out vec4 FragColor;
in vec3 col;
in vec2 texCoord;

uniform vec3 color;
uniform sampler2D uTexture;

void main()
{
	vec4 t = texture(uTexture, texCoord);
	
    FragColor = vec4(t.rgb, 1.0f);
}