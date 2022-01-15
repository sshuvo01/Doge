#version 330 core
out vec4 FragColor;
  
in vec2 v_TexCoords;

uniform sampler2D screenRectTexture;

void main()
{
/*

	float r = texture(screenRectTexture, v_TexCoords).r;
    FragColor = vec4(r, r, r, 1.0);
	*/
	FragColor = texture(screenRectTexture, v_TexCoords);
}