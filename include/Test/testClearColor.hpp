#pragma once

#include <Test/test.hpp>

namespace test {

class TestClearColor: public test {
public:
    TestClearColor(): _clearColor{0.2f, 0.3f, 0.8f, 1.0f} {

    }
    ~TestClearColor() {

    }

public:
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;
private:
    float _clearColor[4];
};

}