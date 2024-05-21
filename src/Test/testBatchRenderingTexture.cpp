#include <Test/testBatchRenderingTexture.hpp>

namespace test {

void testBatchRenderingTexture::init()
{
    vertexBufferLayout layout;
    float vertices[] = {
        -1.5f, -0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,
        -1.5f,  0.5f, 0.0f, 1.0f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,

         0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 1.0f,
         1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };
    int samplers[2] = {0, 1};

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    _va = std::make_unique<vertexArray>();
    _vb = std::make_unique<vertexBuffer>(vertices, static_cast<unsigned int>(8 * 10 * sizeof(float)));
    _ib = std::make_unique<indexBuffer>(indices, 12);
    _shader = std::make_unique<shader>("../res/Shaders/BatchTexture.glsl");
    _renderer = std::make_unique<renderer>();
    _gura = std::make_unique<texture>("../res/img/gura.png");
    _girls = std::make_unique<texture>("../res/img/gwar.jpg");
    
    layout.push<float>(3);
    layout.push<float>(4);
    layout.push<float>(2);
    layout.push<float>(1);
    _va->addBuffer(*_vb, layout);

    _gura->bind(0);
    _girls->bind(1);

    _shader->bind();
    _shader->setUniform1iv("u_textures", 2, samplers);
    
}

void testBatchRenderingTexture::onUpdate(float deltaTime)
{
    
}

void testBatchRenderingTexture::onRender()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    _shader->bind();

    _shader->setUniformMat4f("u_view", _view);
    _shader->setUniformMat4f("u_transform", _translation);

    _renderer->draw(*_va, *_ib, *_shader);
}

void testBatchRenderingTexture::onImGuiRender()
{
    
}

}