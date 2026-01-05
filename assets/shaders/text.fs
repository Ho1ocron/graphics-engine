#version 330 core
in vec2 TexCoords;
out vec4 Color;

uniform sampler2D font;
uniform vec3 textColor;

void main(){
    Color = vec4(textColor * texture(font, TexCoords).r, 1.0);
}
