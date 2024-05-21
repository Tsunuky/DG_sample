#include <indexBuffer.hpp>
#include <openglError.hpp>


indexBuffer::indexBuffer(const unsigned int* data, unsigned int count) : _count(count) {
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCALL(glGenBuffers(1, &_rendererId));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
};
indexBuffer::~indexBuffer() {
	GLCALL(glDeleteBuffers(1, &_rendererId));
};

void indexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
}

void indexBuffer::unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
