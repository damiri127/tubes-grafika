#version 330 core

// output tipe 4 vektor untuk warna
out vec4 FragColor;

// penambahan warna
in vec3 color;

void main(){
	// Format color RGBA karena memiliki 4 vektor
   FragColor = vec4(color, 1.0f);
};
