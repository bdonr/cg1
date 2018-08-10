#version 130

in vec3 vert;
in vec3 vertNormal;

uniform vec4 mycolor;
uniform vec4 matDiffuseColor;
uniform vec4 matAmbientColor;
uniform vec4 matSpecularColor; 
uniform vec4 lightDiffuseColor;
uniform vec4 lightAmbientColor;
uniform vec4 lightSpecularColor;
uniform vec3 lightdirection;
uniform vec3 viewPos;
uniform float scalar;

    void main() {
       	vec3 norm = normalize(vertNormal);
	vec3 lightDir = normalize(lightdirection - vert);

	vec3 viewDir = normalize(viewPos.xyz - vert);
	vec3 reflectDir = reflect(-lightDir, vert); 


	float spec = pow(max(dot(viewDir, reflectDir), 0.0), scalar);
	float diff = max(dot(norm, lightDir), 0.0);


	vec3 ambient  = lightAmbientColor.xyz * matAmbientColor.xyz;
	vec3 diffuse  = lightDiffuseColor.xyz * (diff * matDiffuseColor.xyz);
	vec3 specular = lightSpecularColor.xyz * (spec * matSpecularColor.xyz);
	vec3 alle = (ambient+diffuse+specular);
	gl_FragColor=vec4(alle,1.0);
    }
