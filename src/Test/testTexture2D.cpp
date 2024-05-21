#include <Test/testTexture2D.hpp>
#include <imgui.hpp>

namespace test {

void TestTexture2D::init() {
    vertexBufferLayout layout;
    float position[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,   // 0
         50.0f, -50.0f, 1.0f, 0.0f,   // 1
         50.0f,  50.0f, 1.0f, 1.0f,   // 2
        -50.0f,  50.0f, 0.0f, 1.0f    // 3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //enable la fusion des colour
    GLCALL(glEnable(GL_BLEND));
    //prend la couleur source pour la l'additionner avec la destination - la source pour transparance
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    _va = std::make_unique<vertexArray>();
    _vb = std::make_unique<vertexBuffer>(position, static_cast<unsigned int>(4 * 4 * sizeof(float)));
    _ib = std::make_unique<indexBuffer>(indices, 6);
    _shader = std::make_unique<shader>("../res/Shaders/BasicTexture.glsl");
    _texture = std::make_unique<texture>("../res/img/gura.png");
    _renderer = std::make_unique<renderer>();

    layout.push<float>(2);
    layout.push<float>(2);
    _va->addBuffer(*_vb, layout);
    
    _shader->bind();
    _texture->bind();
    _shader->setUniform1i("u_texture", 0);
}

void TestTexture2D::onUpdate(float deltaTime)
{

}

void TestTexture2D::onRender()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    _shader->bind();

    _model = glm::translate(glm::mat4(1.0f), _translationA); // move un model
    _mvp = _proj * _view * _model;
    _shader->setUniformMat4f("u_MVP", _mvp);
    _renderer->draw(*_va, *_ib, *_shader);

    _model = glm::translate(glm::mat4(1.0f), _translationB); // move un model
    _mvp = _proj * _view * _model;
    _shader->setUniformMat4f("u_MVP", _mvp);
    _renderer->draw(*_va, *_ib, *_shader);
}


void TestTexture2D::onImGuiRender()
{
    {
    
    ImGui::SliderFloat3("Translation A", &_translationA.x, 0.0f, 1024.0f);
    ImGui::SliderFloat3("Translation B", &_translationB.x, 0.0f, 1024.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    
    }
}

   
}