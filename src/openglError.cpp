#include <openglError.hpp>

#include <iostream>

void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL_Error] (" << error << "): " << function << " file: " << file << " l." << line << std::endl;
        return false;
    }
    return true;
}
