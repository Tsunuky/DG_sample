#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <vertexBufferLayout.hpp>
#include <Test/test.hpp>
#include <renderer.hpp>
#include <glm/glm.hpp>

namespace test {

class testBatchRendering: public test {
public:
    testBatchRendering(): _translation(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
    _view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {
        init();
    }
    ~testBatchRendering() {

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
};


}