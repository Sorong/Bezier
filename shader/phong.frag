#version 330
in vec4 fragposition;
in vec4 fragcolor;
in vec4 fragnormal;

out vec4 fragmentColor;

struct MaterialInfo {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};
uniform Material material;

struct Light {
	vec4 pos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
uniform Light light;




uniform bool blinn;







vec4 ambient() {
	return light.ambient * material.ambient;
}
vec4 diffus(vec4 n, vec4 l) {
	return light.diffuse * material.diffuse * max(dot(n,l), 0.0f);
}
vec4 specular(vec4 s, vec4 n) {
	vec4 r = reflect(-s,n); //2*(max(dot(n, s),0.0f)) * n - s;
	vec4 v = normalize(-fragposition);	
	/*if(blinn) {
		vec3 halfway = normalize(v+s);  //s = Lichtposition
		return light.specular * material.specular * pow(max(dot(halfway, n), 0.0), material.shininess);
	} */
	return light.specular * material.specular * pow(max(dot(r, v), 0.0f), material.shininess);
}
vec3 ads(vec4 pos, vec4 n) {
	vec3 s;
	if(light.pos.w == 0.0) {
		s = normalize(vec3(light.pos));
	} else {
		s = normalize(vec3(light.pos-pos));
	}	
	return ambient() + diffus(s, n) + specular(s,n);  //pos?
}

void main()
{
	fragmentColor = ads(vec4(fragposition, 1.0), fragnormal);
}