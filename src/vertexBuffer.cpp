#include <vertexBuffer.hpp>

vertexBuffer::vertexBuffer(const void* data, unsigned int size, GLenum usage) {
	GLCALL(glGenBuffers(1, &_rendererId));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
};

vertexBuffer::~vertexBuffer() {
	GLCALL(glDeleteBuffers(1, &_rendererId));
};

void vertexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}

void vertexBuffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void vertexBuffer::Buffersubdata(unsigned int size, const void *data)
{
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
