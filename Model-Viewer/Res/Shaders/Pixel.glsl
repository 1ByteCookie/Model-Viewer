#version 460 core
out vec4 Output;

in vec3 Normals;
in vec3 FragmentPositions;

uniform vec3 CamPosition;
uniform vec3 MeshColor;
uniform vec3 DirectionalLight;

void main()
{
	vec3 Color				= MeshColor;
	vec3 LightDirection		= normalize(DirectionalLight);
	vec3 SurfaceNormals		= normalize(Normals);
	vec3 Reflection			= reflect(LightDirection, SurfaceNormals);
	vec3 ViewDirection		= normalize(CamPosition - FragmentPositions);

	// AMBIENT
	vec3 Ambient = Color * 0.2f;

	// DIFFUSE
	float DiffuseStrength = max(dot(LightDirection, SurfaceNormals), 0.0f);
	vec3 Diffuse = DiffuseStrength * Color;

	// SPECULAR
	float SpecularStrength = 0.5f;
	float SpecularHighlight = max(pow(dot(ViewDirection, Reflection), 24.0f), 0.0f);
	vec3 Specular = SpecularHighlight * SpecularStrength * Color;

	Output = vec4(Ambient + Diffuse + Specular, 1.0f);
}