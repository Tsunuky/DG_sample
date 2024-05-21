#pragma once

class indexBuffer {
public:
	indexBuffer(const unsigned int* data, unsigned int count);
	~indexBuffer();
public:
	void bind() const;
	void unbind() const;
public:
	inline unsigned int getCount() const { return _count;};
private:
	unsigned int _rendererId;
	unsigned int _count;
};
