// OpenGL Shader Language(GLSL)

#version 330 core
layout (location = 0) in vec3 aPos;
// vektor untuk warna
layout (location = 1) in vec3 aColor;

out vec3 color;

void main(){
	// posisi dari vertex
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   // assign dalam variable color
   color = aColor;
};