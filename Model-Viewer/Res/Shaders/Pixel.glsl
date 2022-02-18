#version 460 core
out vec4 Output;

in vec2 UV;

uniform sampler2D TextureSampler;

void main()
{
	Output = texture(TextureSampler, UV);
}