cmake_minimum_required(VERSION 3.24)
project(opengl_draw LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
message(CMAKE_MODULE_PATH="${CMAKE_MODULE_PATH}")
find_package(glfw3 CONFIG REQUIRED glfw)

include_directories(
  BEFORE "dependencies/Glad/include"
  BEFORE "include/vendor/imGui"
  BEFORE "include/vendor"
  )

add_executable(opengl_draw
  "dependencies/Glad/src/glad.cpp"
  "src/vendor/imGui/imgui.cpp"
  "src/vendor/imGui/imgui_demo.cpp"
  "src/vendor/imGui/imgui_draw.cpp"
  "src/vendor/imGui/imgui_impl_glfw.cpp"
  "src/vendor/imGui/imgui_impl_opengl3.cpp"
  "src/vendor/imGui/imgui_impl_win32.cpp"
  "src/vendor/imGui/imgui_tables.cpp"
  "src/vendor/imGui/imgui_widgets.cpp"
  "src/vendor/stb_image/stb_image.cpp"
  "src/Test/testClearColor.cpp"
  "src/Test/testTexture2D.cpp"
  "src/Test/testBatchRendering.cpp"
  "src/Test/testBatchRenderingTexture.cpp"
  "src/Test/testBatchRenderDynamic.cpp"
  "src/Test/test.cpp"
  "src/main.cpp"
  "src/indexBuffer.cpp"
  "src/openglError.cpp"
  "src/renderer.cpp"
  "src/shader.cpp"
  "src/texture.cpp"
  "src/vertexArray.cpp"
  "src/vertexBuffer.cpp"
  "src/vertexBufferLayout.cpp"
)

#target_include_directories(opengl_basic PRIVATE ./dependencies/Glad/include)
target_include_directories(opengl_draw PRIVATE ./include)
target_link_libraries(opengl_draw glfw)
set_property(TARGET opengl_draw PROPERTY CXX_STANDARD 20)