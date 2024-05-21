#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <vertexBufferLayout.hpp>
#include <Test/test.hpp>
#include <renderer.hpp>
#include <texture.hpp>
#include <glm/glm.hpp>

namespace test {

class testBatchRenderingDynamic: public test {
public:
    testBatchRenderingDynamic(): _translation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
    _view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {
        init();
    }
    ~testBatchRenderingDynamic() {

    }

public:
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;
    void init();

private:
    glm::mat4 _translation;
    glm::mat4 _view;

    std::unique_ptr<vertexArray> _va;
    std::unique_ptr<vertexBuffer> _vb;
    std::unique_ptr<indexBuffer> _ib;

    std::unique_ptr<shader> _shader;
    std::unique_ptr<renderer> _renderer;
    std::unique_ptr<texture> _gura;
    std::unique_ptr<texture> _girls;
    float _quadPositionA[2] = {-1.5f, -0.5f};
    float _quadPositionB[2] = {0.5f, -0.5f};
};


}