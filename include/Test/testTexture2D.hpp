#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <vertexBufferLayout.hpp>
#include <Test/test.hpp>
#include <renderer.hpp>
#include <glm/glm.hpp>
#include <texture.hpp>

#include <iostream>

namespace test {

class TestTexture2D: public test {
public:
    TestTexture2D(): _translationA(200, 200, 0), _translationB(400, 200, 0),
        _proj(glm::ortho(0.0f, 1280.0f, 0.0f, 1024.0f, -1.0f, 1.0f)),
        _view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {
        init();
    }
    ~TestTexture2D() {

    }

public:
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;
    void init();

private:
    glm::vec3 _translationA;
    glm::vec3 _translationB;
    glm::mat4 _proj;
    glm::mat4 _view;
    glm::mat4 _model;
    glm::mat4 _mvp;

    std::unique_ptr<vertexArray> _va;
    std::unique_ptr<vertexBuffer> _vb;
    std::unique_ptr<indexBuffer> _ib;

    std::unique_ptr<shader> _shader;
    std::unique_ptr<texture> _texture;
    std::unique_ptr<renderer> _renderer;
};

}