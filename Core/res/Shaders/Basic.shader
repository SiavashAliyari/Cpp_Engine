#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

//varying going to the fragement shader
out vec2 v_uv;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    v_uv=uv;
}

#shader fragment

#version 330 core
out vec4 FragColor;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_uv;

void main()
{
    vec4 texColor=texture(u_Texture,v_uv);
    FragColor = texColor*u_Color;
}