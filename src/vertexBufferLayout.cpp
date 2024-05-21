#include <vertexBufferLayout.hpp>
 /*
template<typename T>
inline void push(int count) {
	static_asser(false);
}
template<>
inline void VertexBufferLayout::push<float>(unsigned int count) {
	_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
	_stride += vertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}
template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count) {
	_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
	_stride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}
template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count) {
	_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
	_stride += vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}
*/