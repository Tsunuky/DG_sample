#include <Test/testBatchRendering.hpp>

namespace test {

void testBatchRendering::init()
{
    vertexBufferLayout layout;
    float vertices[] = {
        -1.5f, -0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f,
        -1.5f,  0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f,

         0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
         1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
         1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    _va = std::make_unique<vertexArray>();
    _vb = std::make_unique<vertexBuffer>(vertices, static_cast<unsigned int>(8 * 7 * sizeof(float)));
    _ib = std::make_unique<indexBuffer>(indices, 12);
    _shader = std::make_unique<shader>("../res/Shaders/BatchColor.glsl");
    _renderer = std::make_unique<renderer>();
    
    layout.push<float>(3);
    layout.push<float>(4);
    _va->addBuffer(*_vb, layout);

}

void testBatchRendering::onUpdate(float deltaTime)
{
    
}

void testBatchRendering::onRender()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    _shader->bind();

    _shader->setUniformMat4f("u_view", _view);
    _shader->setUniformMat4f("u_transform", _translation);

    _renderer->draw(*_va, *_ib, *_shader);
}

void testBatchRendering::onImGuiRender()
{
    
}

}