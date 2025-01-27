#pragma once

#include <glad/glad.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) glClearError();x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, int line);