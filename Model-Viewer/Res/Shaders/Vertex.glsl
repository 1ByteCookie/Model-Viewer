#version 460 core

layout(location = 0) in vec3 _VertexPosition_;
layout(location = 1) in vec3 _Normals_;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Normals;
out vec3 FragmentPositions;

void main()
{
	Normals = mat3(Model) * _Normals_;
	FragmentPositions = vec3( Model * vec4(_VertexPosition_, 1.0f) );

	gl_Position = Projection * View * Model * vec4(_VertexPosition_, 1.0f);
}