#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	
	glGenBuffers(1, &ID);
	// Mengikat VBO dengan menentukan bahwa itu adalah GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER,size,  vertices, GL_STATIC_DRAW);

}

void VBO::Bind() {
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}