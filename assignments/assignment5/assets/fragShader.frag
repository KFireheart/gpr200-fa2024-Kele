#version 330 core
out vec4 FragColor;
out vec3 ambient;
 
in vec2 TexCoord;
in vec3 ourColor;
in vec3 normal;
in vec3 FragPos;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    FragColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.5);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);

}