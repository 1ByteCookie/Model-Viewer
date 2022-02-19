#version 460 core

layout(location = 0) in vec3 _VertexPosition_;
layout(location = 1) in vec2 _UV_;

out vec2 UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	UV = _UV_;

	gl_Position = Projection * View * Model * vec4(_VertexPosition_, 1.0f);
}