#include <Test/testBatchRenderDynamic.hpp>
#include <imgui.hpp>
#include <array>

namespace test {

struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x;
    float y;
    float z;
};

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct vertex {
    vec3 Position;
    vec4 Color;
    vec2 TextCoord;
    float TextIndex;
};

void testBatchRenderingDynamic::init()
{
    vertexBufferLayout layout;
    // function qui genere ce patterne par rapport au nbr de vertex
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };
    int samplers[2] = {0, 1};

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    _va = std::make_unique<vertexArray>();
    _vb = std::make_unique<vertexBuffer>(nullptr, static_cast<unsigned int>(8 * sizeof(vertex), GL_DYNAMIC_DRAW));
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

static std::array<vertex, 4> createQuad(float x, float y, float textureId)
{
    float size = 1.0f;

    vertex v1;
    v1.Position = {x, y, 0.0f};
    v1.Color = {1.0f, 0.6f, 0.96f, 1.0f};
    v1.TextCoord = {0.0f, 0.0f};
    v1.TextIndex = textureId;

    vertex v2;
    v2.Position = {x + size, y, 0.0f};
    v2.Color = {1.0f, 0.6f, 0.96f, 1.0f};
    v2.TextCoord = {1.0f, 0.0f};
    v2.TextIndex = textureId;

    vertex v3;
    v3.Position = {x + size,  y + size, 0.0f};
    v3.Color = {1.0f, 0.6f, 0.96f, 1.0f};
    v3.TextCoord = {1.0f, 1.0f};
    v3.TextIndex = textureId;

    vertex v4;
    v4.Position = {x,  y + size, 0.0f};
    v4.Color = {1.0f, 0.6f, 0.96f,1.0f};
    v4.TextCoord = {0.0f, 1.0f};
    v4.TextIndex = textureId;

    return {v1, v2, v3, v4};
}

void testBatchRenderingDynamic::onUpdate(float deltaTime)
{
    vertex vertices[8];
    auto q0 = createQuad(_quadPositionA[0], _quadPositionA[1], 0.0f);
    auto q1 = createQuad(_quadPositionB[0], _quadPositionB[1], 1.0f);

    memcpy(vertices, q0.data(), q0.size() * sizeof(vertex));
    memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(vertex));

    _vb->bind();
    _vb->Buffersubdata(sizeof(vertices), vertices);
}

void testBatchRenderingDynamic::onRender()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    _shader->bind();

    _shader->setUniformMat4f("u_view", _view);
    _shader->setUniformMat4f("u_transform", _translation);

    _renderer->draw(*_va, *_ib, *_shader);
}

void testBatchRenderingDynamic::onImGuiRender()
{
    ImGui::DragFloat2("Quad PositionA", _quadPositionA, 0.1f);
    ImGui::DragFloat2("Quad PositionB", _quadPositionB, 0.1f);
}

}