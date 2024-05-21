#include <renderer.hpp>

#include <iostream>
#include <openglError.hpp>

/*void glClearError()
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
}*/

void renderer::draw(const vertexArray &va, const indexBuffer &ib, const shader &shader) const
{
    shader.bind();
    //shader.setUniform4f("u_color", r, 0.3f, 0.8f,//  1.0f);
    va.bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void renderer::clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
