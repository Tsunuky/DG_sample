#pragma once

#include <openglError.hpp>
#include <stb_image\stb_image.hpp>
#include <string>

#include <iostream>

class texture {
public:
	texture(const std::string &path):
		_rendererId(0), _filepath(path), _localBuffer(nullptr), _width(0), _height(0), _BPP(0) {
		//unsigned char *_localBuffer;
		stbi_set_flip_vertically_on_load(1);
		_localBuffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 4);

		GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId));
		GLCALL(glBindTexture(GL_TEXTURE_2D, _rendererId));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
		if (_localBuffer)
			stbi_image_free(_localBuffer);
	}
	~texture() {
		GLCALL(glDeleteTextures(1, &_rendererId));
	}
public:
	void bind(unsigned int slot = 0) const;
	void unbind() const;
public:
	inline int getWidth() const { return _width;}
	inline int getHeight() const { return _height;}
	inline int getID() const { return _rendererId;}
private:
	unsigned int _rendererId;
	std::string _filepath;
	unsigned char *_localBuffer;
	int _width;
	int _height;
	int _BPP;
};