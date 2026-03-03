#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_UV;

layout(location = 2) in mat4 a_Model;

uniform mat4 u_ViewProj;

out vec2 v_uv;

void main()
{
    v_uv = a_UV;
    gl_Position = u_ViewProj * a_Model * vec4(a_Pos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 v_uv;

uniform sampler2D u_Texture;

void main()
{
    vec4 c = texture(u_Texture, v_uv);
    FragColor = c;
}