#version 430
in vec4 fragposition;
in vec4 fragcolor;
in vec4 fragnormal;

out vec4 fragmentColor;

struct Material {
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







vec3 ambient() {
	return vec3(light.ambient * material.ambient);
}
vec3 diffus(vec3 n, vec3 l) {
	return vec3(light.diffuse * material.diffuse * max(dot(n,l), 0.0f));
}
vec3 specular(vec3 s, vec3 n) {
	vec3 r = reflect(-s,n); //2*(max(dot(n, s),0.0f)) * n - s;
	vec3 v = normalize(-vec3(fragposition));	
	/*if(blinn) {
		vec3 halfway = normalize(v+s);  //s = Lichtposition
		return light.specular * material.specular * pow(max(dot(halfway, n), 0.0), material.shininess);
	} */
	return vec3(light.specular * material.specular) * pow(max(dot(r, v), 0.0f), material.shininess);
}
vec3 ads(vec4 pos, vec3 n) {
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
	float alpha = fragcolor.w;
	vec3 col = ads(fragposition, vec3(fragnormal));
	fragmentColor = vec4(col, alpha);
}