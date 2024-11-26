#version 460 core

in vec4 color;

out vec4 fragColor;

void main() {
	fragColor = color;
	fragColor = vec4(1, 0, 0, 1);
}