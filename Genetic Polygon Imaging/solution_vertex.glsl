#version 460 core

uniform float width;
uniform float height;

layout(location = 0) in uvec2 position;
layout(location = 1) in uvec4 in_color;

out vec4 color;

void main() {
	vec2 screenSpace = vec2(position.x / width, position.y / height);
	screenSpace = ((screenSpace) * 2) - 1;
	gl_Position = vec4(screenSpace, 0, 1);
	color = in_color / 255.0f;
}