#include <Test/testClearColor.hpp>
#include <openglError.hpp>
#include <imgui.hpp>

namespace test {

void TestClearColor::onUpdate(float deltaTime)
{

}

void TestClearColor::onRender()
{
    GLCALL(glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}


void TestClearColor::onImGuiRender()
{
    ImGui::ColorPicker4("clear color", _clearColor);
}

}