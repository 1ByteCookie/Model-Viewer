#version 460 core

layout(location = 0) in vec3 _VertexPosition_;
layout(location = 1) in vec2 _UV_;

out vec2 UV;

void main()
{
	UV = _UV_;

	gl_Position = vec4(_VertexPosition_, 1.0f);
}