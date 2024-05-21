#include <Test/test.hpp>

#include <imgui.hpp>

namespace test {

void testMenu::onUpdate(float deltaTime)
{

}

void testMenu::onRender()
{

}

void testMenu::onImGuiRender()
{
    ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);

    ImGui::SeparatorText("Exercice");
    for (auto &test : _listTest) {
        if (ImGui::Button(test.first.c_str(), sz))
            _current = test.second();
        //if (ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
        //    ImGui::SetTooltip("l'ets clear screen color"); rajouter ca
    }
}

}