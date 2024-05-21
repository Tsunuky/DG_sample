#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <imgui.hpp>
#include <imgui_impl_glfw.hpp>
#include <imgui_impl_opengl3.hpp>

#include <Test/testClearColor.hpp>
#include <Test/testTexture2D.hpp>
#include <Test/testBatchRendering.hpp>
#include <Test/testBatchRenderingTexture.hpp>
#include <Test/testBatchRenderDynamic.hpp>

#include <iostream>
#include <cstring>

void drawBackButton(test::test *&currenTest, test::testMenu *&menuTest)
{
    if (currenTest != menuTest && ImGui::Button("<-")) {
        delete currenTest;
        currenTest = menuTest;
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!(window = glfwCreateWindow(1280, 1024, "Hello World", NULL, NULL))) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    gladLoadGL();
    std::cout << glGetString(GL_VERSION) << std::endl;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
    ImGui::StyleColorsDark();

    test::test *currenTest = nullptr;
    test::testMenu *menuTest = new test::testMenu(currenTest);

    currenTest = menuTest;
    menuTest->registerTest<test::TestClearColor>("Clear color");
    menuTest->registerTest<test::TestTexture2D>("Texture 2D");
    menuTest->registerTest<test::testBatchRendering>("Batch rendering");
    menuTest->registerTest<test::testBatchRenderingTexture>("Batch rendering texture");
    menuTest->registerTest<test::testBatchRenderingDynamic>("Batch rendering dynamic");

    while (!glfwWindowShouldClose(window)) {
        GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        assert(currenTest != nullptr);
        currenTest->onUpdate(0.0f);
        currenTest->onRender();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("test");
        currenTest->onImGuiRender();
        drawBackButton(currenTest, menuTest);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (currenTest != menuTest)
        delete menuTest;
    delete currenTest;
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
