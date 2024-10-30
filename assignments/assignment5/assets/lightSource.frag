#version 330 core

in vec3 normal;
in vec3 fragPos;
uniform vec3 lightPos;

void main(){
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
}
