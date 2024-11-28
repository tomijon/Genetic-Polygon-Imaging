#version 460 core

uniform sampler2D drawTex;

in vec2 texcoord;

out vec4 color;

void main() {
	color = texture(drawTex, texcoord);
}