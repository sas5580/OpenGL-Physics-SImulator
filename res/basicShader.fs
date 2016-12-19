#version 130

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;

vec3 lightDirection = vec3(0,0,1);

void main()
{
	gl_FragColor = vec4(1, 0, 0, 1);
	/*
	gl_FragColor = texture2D(sampler, texCoord0)
		* clamp(-1*normal0.z, 0.0, 1.0); //lambertian lighting
	*/
}