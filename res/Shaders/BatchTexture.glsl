#shader vertex
#version 450 core
#pragma debug(on)

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textCoord;
layout(location = 3) in float a_textIndex;

uniform mat4 u_view;
uniform mat4 u_transform;

out vec4 v_color;
out vec2 v_textCoord;
out float v_textIndex;

void main()
{
    v_color = a_color;
    v_textCoord = a_textCoord;
    v_textIndex = a_textIndex;
    gl_Position = u_view * u_transform * vec4(a_position, 1.0);
}

#shader fragment
#version 450 core
#pragma debug(on)

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_textCoord;
in float v_textIndex;

uniform sampler2D u_textures[2];

void main()
{
    //color = vec4(v_textCoord, 0.0, 1.0);
    //pour tester si les texture coord sont bonne carre vert rouge

    //color = vec4(v_textIndex, v_textIndex, v_textIndex, 1.0);
    //pour tester il prend des texture differente un blanc lautre noir

    int index = int(v_textIndex);

    color = texture(u_textures[index], v_textCoord);
}