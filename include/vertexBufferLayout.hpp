#pragma once

#include <glad/glad.hpp>

#include <openglError.hpp>
#include <vector>

struct vertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return sizeof(GLfloat);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class vertexBufferLayout {
public:
	vertexBufferLayout(): _stride(0) {}
	~vertexBufferLayout() = default;
public:
	template<typename T>
	void push(unsigned int count) = delete;

	template<>
	void push<float>(unsigned int count) {
		_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
		_stride += vertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
		_stride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
		_stride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
public:
	inline unsigned int getStride() const { return _stride; };
	inline const std::vector<vertexBufferElement> &getElement() const { return _elements; };
private:
	std::vector<vertexBufferElement> _elements;
	unsigned int _stride;
};
