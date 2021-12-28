#version 330 core
out vec4 FragColor;
  
in vec2 v_TexCoords;

uniform sampler2D screenRectTexture;

void main()
{ 
    FragColor = texture(screenRectTexture, v_TexCoords);
}