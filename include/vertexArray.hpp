#pragma once

#include <vertexBuffer.hpp>

class vertexBufferLayout;

class vertexArray {
public:
	vertexArray();
	~vertexArray();
public:
	void addBuffer(const vertexBuffer &vb, const vertexBufferLayout &layout);
	void bind() const;
	void unbind() const;
private:
	unsigned int _rendererId;
};
