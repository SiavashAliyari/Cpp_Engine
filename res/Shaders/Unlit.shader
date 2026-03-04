#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 uv;

uniform mat4 u_MVP;
//varying going to the fragement shader
out vec2 v_uv;
out vec3 v_norm;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    v_uv=uv;
    v_norm=aNorm;
}

#shader fragment

#version 330 core
out vec4 FragColor;
uniform vec4 u_Color;
uniform sampler2D texture_diffuse1;
uniform vec3 u_Directional_Light;
uniform float u_Ambient;

in vec2 v_uv;
in vec3 v_norm;

void main()
{
    vec3 norm=normalize(v_norm);
    float diff = max(dot(norm, normalize(u_Directional_Light)), 0.0);
    vec4 ambient=vec4(u_Ambient,u_Ambient,u_Ambient,1.0f);
    vec4 final_color=texture(texture_diffuse1,v_uv)*(diff+ambient);

    FragColor = final_color;

}