#pragma once

#include <openglError.hpp>

class vertexBuffer {
public:
	vertexBuffer(const void *data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
	~vertexBuffer();

public:
	void bind() const;
	void unbind() const;

public:
	void Buffersubdata(unsigned int size, const void *data);

private:
	unsigned int _rendererId;
};
