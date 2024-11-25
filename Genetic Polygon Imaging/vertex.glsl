#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 in_color;

out vec4 color;

void main() {
	gl_Position = vec4(position, 0, 1);
	color = in_color;
}