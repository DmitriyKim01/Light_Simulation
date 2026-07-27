#version 330 core

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3  direction;
    float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{	
	vec4 result = vec4(0.0);
	vec3 lightDir = normalize(light.position - FragPos); 
	float theta = dot(lightDir, normalize(-light.direction));

	if(theta > light.cutOff) {
		// ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

		// diffuse
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));  

		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

		// attenuation
		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + 
    				light.quadratic * (distance * distance));  
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		result = vec4(ambient + diffuse + specular, 1.0);
	} else {
		result = vec4(light.ambient * vec3(texture(material.diffuse, TexCoord)), 1.0);
	}

	FragColor = result;
}