#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec2 v_uv;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    v_uv = uv;
}


#shader fragment

#version 330 core
out vec4 FragColor;

in vec2 v_uv;
uniform sampler2D u_Texture;
uniform bool u_blackAndWhite;
uniform bool u_tint;
uniform vec4 u_tint_color;
void main()
{
    vec4 texColor=texture(u_Texture,v_uv);
   
    vec4 finalColor=texColor;

    if(u_tint){
        finalColor+=u_tint_color;
    }
    if(u_blackAndWhite){
        float gray = 0.33 * (texColor.r + texColor.g + texColor.b);
        finalColor=vec4(gray);
    }
    FragColor = finalColor;
}