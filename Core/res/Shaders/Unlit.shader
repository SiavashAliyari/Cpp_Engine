#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 uv;

uniform mat4 u_MVP;
//varying going to the fragement shader
out vec2 v_uv;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    v_uv=uv;
}

#shader fragment

#version 330 core
out vec4 FragColor;
uniform vec4 u_Color;
uniform sampler2D texture_diffuse1;

in vec2 v_uv;

void main()
{
    FragColor = texture(texture_diffuse1,v_uv);
}