#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform float specularStrength;
uniform float shininess;
uniform float ambientStrength;
uniform float diffuseStrength;

void main()
{
    // Ambient lighting
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * diffuseStrength;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine ambient, diffuse, and specular lighting
    vec3 lighting = ambient + diffuse + specular;

    // Sample the texture color and apply lighting
    vec4 texColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.5);
    FragColor = vec4(lighting, 1.0) * texColor;
}