#include"VAO.h"

VAO::VAO() {
	// Hasilkan VAO dan VBO dengan hanya 1 objek masing-masing
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type,GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}


void VAO::Bind() {
	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(0);
}

void VAO::Delete() { 
	// Delete all the objects we've created
	glDeleteVertexArrays(1, &ID);
}