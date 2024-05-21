#include <texture.hpp>

/*texture::texture(const std::string &path):
	_rendererId(0), _filepath(path), _localBuffer(nullptr), _width(0), _height(0), _BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	_localBuffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 4);

	GLCALL(glGenTextures(1, &_rendererId));
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

texture::~texture()
{
	GLCALL(glDeleteTextures(1, &_rendererId));
}
*/

void texture::bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, _rendererId));
}

void texture::unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}