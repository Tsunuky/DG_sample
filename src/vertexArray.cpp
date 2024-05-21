#include <vertexArray.hpp>
#include <vertexBufferLayout.hpp>

#define BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

vertexArray::vertexArray() {
	GLCALL(glGenVertexArrays(1, &_rendererId));
	GLCALL(glBindVertexArray(_rendererId))
};

vertexArray::~vertexArray() {
	GLCALL(glDeleteVertexArrays(1, &_rendererId));
};

#include <iostream>

void vertexArray::addBuffer(const vertexBuffer &vb, const vertexBufferLayout &layout)
{
	std::vector<vertexBufferElement> elements = layout.getElement();
	unsigned int offset = 0;

	bind();
	vb.bind();
	for (unsigned int i = 0; i < elements.size(); i++) {
		const vertexBufferElement element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), BUFFER_OFFSET(offset))); // link le buffer au vao
		offset += element.count * vertexBufferElement::getSizeOfType(element.type);
	}

}

void vertexArray::bind() const
{
	GLCALL(glBindVertexArray(_rendererId));
}

void vertexArray::unbind() const
{
	GLCALL(glBindVertexArray(0));
}