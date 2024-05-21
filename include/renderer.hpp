#pragma once

#include <glad/glad.hpp>

#include <indexBuffer.hpp>
#include <vertexArray.hpp>
#include <shader.hpp>

//#define ASSERT(x) if (!(x)) __debugbreak();
//#define GLCALL(x) glClearError();x;\
//    ASSERT(glLogCall(#x, __FILE__, __LINE__))

//void glClearError();
//bool glLogCall(const char* function, const char* file, int line);

class renderer {
public:
    renderer() {}
    ~renderer() = default;
public:
    void clear() const;
    void draw(const vertexArray &va, const indexBuffer &ib, const shader &shader) const;
private:
};
